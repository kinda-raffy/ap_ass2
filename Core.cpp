#include "Core.h"

void Core::printDuck() {
    std::cout << "https://imgur.com/gallery/w9Mjo4y" << std::endl;
}

Core::Core(const std::vector<std::string> &players)
        : bag {std::move(Core::createBag())}, board {std::make_shared<Board>()},
          current {0} {
    // For each player name, add a new player object to the core players.
    for (const std::string &name : players) {
        this->players.emplace_back(name, bag);
    }
}

Core::Core(SaveState &save)
    : bag {std::make_shared<LinkedList>(save.getTiles())},
      board {std::make_shared<Board>(save.getBoard())}, 
      current {save.getCurrent()} {
    // Read save state strings into local vectors.
    std::shared_ptr<std::vector<std::string>> names {save.getPlayers()},
        hands {save.getHands()};
    std::shared_ptr<std::vector<int>> scores {save.getScores()};
    std::size_t index {0}, bound {names->size()};
    // Construct new player objects from all corresponding strings.
    while (index < bound) {
        Player player {names->at(index), hands->at(index), scores->at(index)};
        players.emplace_back(player);
        ++index;
    }
}

void Core::changeTurn() {
    current = (current >= players.size() - 1) ? 0 : current + 1;
}

void Core::getInput(std::vector<std::string> &action) {
    std::cout << "> " << std::flush;
    std::string word {}, input {};
    // Process user's selected action into a vector of strings.
    std::getline(std::cin >> std::ws, input);
    if (!std::cin.eof()) {
        std::stringstream stream {input};
        bool save {false};
        // Iterate over individual words in user input.
        while (stream >> word) {
            // If not save directive, convert to uppercase for robust handling.
            if (!save) {
                std::transform(word.begin(), word.end(), word.begin(), toupper);
            }
            // Detects if the input action is a save directive.
            save = word == "SAVE";
            action.emplace_back(word);
        }
    } else {
        // If the end of standard input is reached, signal to quit.
        action.emplace_back("QUIT");
    }
}

void Core::runCore() {
    control = NEXT;
    do {
        // Print the context-appropriate prompt to standard output for player.
        if (control != Control::INVALID && control != Control::SAME) {
            displayTurn();
        } else if (control == Control::INVALID) {
            std::cout << "Invalid Input" << std::endl;
        }
        std::vector<std::string> action {};
        // Retrieve user input and handle the specified action.
        getInput(action);
        doAction(action);
        // Update core state if either control is encountered.
        if (control == Control::NEXT) {
            changeTurn();
        }
    } while (control != Control::QUIT);
    displayEnd();
}

void Core::saveCore(const std::string &file) {
    // Create a new save state object using the current state of core.
    auto save {std::make_unique<SaveState>(*this)};
    save->saveToFile(file);
}

void Core::doAction(const std::vector<std::string> &action) {
    Player &player {players.at(current)};
    control = Control::INVALID;
    // If any action has been specified, handle that action.
    if (!action.empty()) {
        handleAction(player, action);
    }
    // If the player has exceeded pass bound or no tiles are left, signal quit.
    if (player.getPass() == 2
        || !(bag->size() || player.getHand()->size())) {
        control = Control::QUIT;
    }
}

void Core::handleAction(Player &player,
    const std::vector<std::string> &action) {
    // Extract the base action.
    const std::string type {action.at(0)};
    if (type == "PLACE") {
        handlePlace(player, action);
    } else if (type == "REPLACE" && !player.isPlacing()) {
        replaceTile(player, action);
    } else if (type == "PASS" && !player.isPlacing()) {
        // Update player object pass count and signal core to next player.
        player.incrementPass();
        control = Control::NEXT;
    } else if (type == "SAVE" && action.size() == 2 && !player.isPlacing()) {
        // Save core state to file provided and signal core keep this turn.
        saveCore(action.at(1));
        control = Control::SAME;
    } else if (type == "QUIT") {
        control = Control::QUIT;
    }
}

void Core::handlePlace(Player &player, const std::vector<std::string> &action) {
    control = Control::INVALID;
    // If player has finished placing tiles and received args are correct.
    if (action.size() == 2 && action.at(1) == "DONE" && player.isPlacing()) {
        placeDone(player);
    } else if (action.size() == 4
        && action.at(2) == "AT"
        && player.getHand()->contains(action.at(1).at(0))) {
        // If the args are correct and the hand contains letter to place.
        placeTile(player, action);
    }
}

void Core::placeDone(Player &player) {
    std::size_t handSize {player.getHand()->size()};
    // Replenish player's hand whilst there are still tiles in bag.
    while (bag->size() > 0 && handSize < HAND_SIZE) {
        player.getHand()->append(bag->pop());
        ++handSize;
    }
    // Signal core transition to next player and reset turn-specific data.
    player.donePlacing();
    control = Control::NEXT;
}

void Core::placeTile(Player &player, const std::vector<std::string> &action) {
    control = Control::INVALID;
    int score = verifyPlace(player, action) ? insertTile(action) : 0;
    // If the player's action was valid.
    if (score != 0) {
        // Delete placed tile from player's hand and reset player state.
        std::shared_ptr<LinkedList> hand {player.getHand()};
        hand->remove(action.at(1).at(0));
        player.updatePlace(action.at(3));
        player.refreshPass();
        player.startPlacing();
        // Calculate the score, including checking for bingo.
        if (hand->size() == 0) {
            std::cout << "\nBINGO!!!\n\n";
            score += BINGO_BONUS;
        }
        // Add score to player object, and signal core to stay on turn.
        player.addScore(score);
        control = Control::SAME;
    }
}

int Core::insertTile(const std::vector<std::string> &action) {
    std::string position {action.at(3)};
    // Derive row and col positions, try .
    return board->placeTile(
        std::toupper(position.at(0)) - 65, std::stoi(position.substr(1)),
        static_cast<char>(std::toupper(action.at(1).at(0)))
    );
}

bool Core::verifyPlace(Player &player, const std::vector<std::string> &action) {
    bool valid {true};
    // Retrieve the current tile to be placed and the previously placed tile.
    const std::string prev {player.prevTile()}, curr {action.at(3)};
    // If the player has placed at least another tile this turn.
    if (!prev.empty()) {
        // Extract all relevant coordinate info in workable data types.
        const std::size_t 
            prevRow {static_cast<std::size_t>(prev.at(0) - 65)},
            currRow {static_cast<std::size_t>(curr.at(0) - 65)},
            prevCol {static_cast<std::size_t>(std::stoi(prev.substr(1)))},
            currCol {static_cast<std::size_t>(std::stoi(curr.substr(1)))};
        std::size_t hi, lo;
        Direction direction {player.getDirection()};
        bool xAxis {prevRow == currRow}, yAxis {prevCol == currCol};
        // Coordinates correspond horizontally, player isn't placing vertically.
        if (xAxis && direction != Direction::Y_AXIS) {
            // Establish the range of positions to be validated on board.
            hi = std::max(prevCol, currCol);
            lo = std::min(prevCol, currCol) + 1;
            // Iterate over identified positions to ensure they're filled.
            while (lo < hi && valid) {
                valid = board->getLetter(currRow, lo) != '-';
                ++lo;
            }
        // Coordinates correspond vertically, player isn't placing horizontally.
        } else if (yAxis && direction != Direction::X_AXIS) {
            // Establish the range of positions to be validated on board.
            hi = std::max(prevRow, currRow);
            lo = std::min(prevRow, currRow) + 1;
            // Iterate over identified positions to ensure they're filled.
            while (lo < hi && valid) {
                valid = board->getLetter(lo, currCol) != '-';
                ++lo;
            }
        } else {
            // If the action corresponds in neither direction, it's invalid.
            valid = false;
        }
    }
    // Return if action is valid in context of player's turn.
    return valid;
}

void Core::replaceTile(Player &player, const std::vector<std::string> &action) {
    control = Control::INVALID;
    player.refreshPass();
    // Get replace character and check for valid input.
    std::string letter {action.at(1)};
    if (letter.size() == 1 
        && player.getHand()->replace(letter.at(0), bag->pop())) {
        // If valid and replaced tile in hand, put exchanged tile in bag.
        bag->append(letter.at(0));
        control = Control::NEXT;
    }
}

std::unique_ptr<LinkedList> Core::createBag() {
    auto tiles {std::make_unique<LinkedList>()};
    std::ifstream file {"ScrabbleTiles.txt"};
    if (file) {
        // Create buffer vector and preallocate storage to avoid resizing.
        std::vector<char> characters {};
        characters.reserve(100);
        std::string line {};
        // Extract the character for each line; value unnecessary. 
        while (std::getline(file, line)) {
            characters.push_back(line.at(0));
        }
        // Close file connection once all data is acquired.
        file.close();
        // Shuffle the buffer list so characters are read in random order.
        std::default_random_engine 
            rand(std::chrono::system_clock::now().time_since_epoch().count());
        std::shuffle(characters.begin(), characters.end(), rand);
        // Append reordered characters to linked list.
        for (char character : characters) {
            tiles->append(character);
        }
    } else {
        // throw std::runtime_error("Could not open tile bag file");
        std::cout << "Could not open tile bag file" << std::endl;
    }
    return tiles;
}

void Core::displayTurn() {
    // Display indication of current player's turn.
    std::cout << std::endl 
        << players.at(current).getName() << " it's your turn.\n";
    // Display scores for each player.
    for (const auto &player : players) {
        std::cout 
            << "Score for " << player.getName()
            << ": " << player.getScore() << std::endl;
    }
    // Display tiles in current player's hand.
    std::cout 
        << board->toString() << "\n\n"
        << "Your hand is\n" << players.at(current).handToString() << "\n\n";
}

void Core::displayEnd() {
    std::cout << "\nGame over\n";
    // Print scoreboard.
    for (auto &player : players) {
        std::cout
            << "Score for " << player.getName()
            << ": " << player.getScore() << std::endl;
    }
    bool tie {players.at(0).getScore() == players.at(1).getScore()};
    // Find and declare winner by checking player scores if there are any.
    if (tie) {
        std::cout << "It's a tie!\n" << std::endl;
    } else {
        auto victor { std::max_element(players.begin(), players.end(),
            [](const Player &a, const Player &b) {
                return a.getScore() < b.getScore();
            })[0]
        };
        std::cout << "Player " << victor.getName() << " won!\n\n";
    }
}

std::shared_ptr<std::vector<Player>> Core::getPlayers() {
    return std::make_shared<std::vector<Player>>(players);
}

std::shared_ptr<LinkedList> Core::getBag() {
    return bag;
}

std::shared_ptr<Board> Core::getBoard() {
    return board;
}

std::size_t Core::getCurrent() const {
    return current;
}

