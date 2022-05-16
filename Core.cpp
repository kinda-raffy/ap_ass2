#include "Core.h"

void Core::printDuck() {
    std::cout << "https://imgur.com/gallery/w9Mjo4y" << std::endl;
}

/**
 * @brief Construct a new core object with the given player names.
 * @param players The name of each player in the new game.
 */
Core::Core(const std::vector<std::string> &players) 
    : bag {std::move(Core::createBag())}, board {std::make_shared<Board>()}, 
      current {0} {
    // For each player name, add a new player object to the core players.
    for (const std::string &name : players) {
        this->players.emplace_back(name, bag);
    }
}

/**
 * @brief Construct a core object using previous game data.
 * @param save The save state object encapsulating desired previous game data.
 */
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

/**
 * @brief Move to the next player by updating internal core state.
 */
void Core::changeTurn() {
    current = (current >= players.size() - 1) ? 0 : current + 1;
}

/**
 * @brief Read the user's desired action from standard input.
 * @param action Vector that user's decision should be read into.
 */
void Core::getInput(std::vector<std::string> &action) {
    std::cout << "> " << std::flush;
    std::string word {}, input {};
    // Process user's selected action into a vector of strings.
    std::getline(std::cin >> std::ws, input);
    if (!std::cin.eof()) {
        std::stringstream stream {input};
        while (stream >> word) {
            action.emplace_back(word);
        }
    } else {
        // If the end of standard input is reached, signal to quit.
        action.emplace_back("quit");
    }
}

/**
 * @brief Main function to initiate a new game with data stored in core fields.
 * Loops for each user action until a sequence of events which signals quit.
 */
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
        if (control == Control::QUIT) {
            displayEnd();
        } else if (control == Control::NEXT) {
            changeTurn();
        }
    } while (control != Control::QUIT);
    std::cout << "Goodbye" << std::endl;
}

/**
 * @brief Convert current internal core state to strings and save to file.
 * @param file File title where the core save state should be stored.
 */
void Core::saveCore(const std::string &file) {
    // Create a new save state object using the current state of core.
    auto save {std::make_unique<SaveState>(*this)};
    save->saveToFile(file);
}

/**
 * @brief Ensure an action exists and update state after action is performed.
 * If no tiles are left in the bag or either player hand, or a player exceeds
 * their allocated pass limit, the game will terminate.
 * @param action The strings specifying action to be performed.
 */
void Core::doAction(const std::vector<std::string> &action) {
    Player &player {players.at(current)};
    control = Control::INVALID;
    if (!action.empty()) {
        handleAction(player, action);
    }
    if (player.getPass() == 2 
        || !(bag->size() || player.getHand()->size())) {
        control = Control::QUIT;
    }
}

/**
 * @brief Delegate processes based on type of user's specified action.
 * Core's internal flow control is automatically updated given certain
 * conditions: if the player has passed, move to the next player; if the
 * game has been saved remain on the same player, and quit if the player
 * has chosen to do so.
 * @param player Reference to the player object whose term
 * @param action 
 */
void Core::handleAction(Player &player, 
    const std::vector<std::string> &action) {
    // Extract the base action.
    const std::string type {action.at(0)};
    if (type == "place") {
        handlePlace(player, action);
    } else if (type == "replace" && !player.isPlacing()) {
        replaceTile(player, action);
    } else if (type == "pass" && !player.isPlacing()) {
        // Update player object pass count and signal core to next player.
        player.incrementPass();
        control = Control::NEXT;
    } else if (type == "save" && action.size() == 2 && !player.isPlacing()) {
        // Save core state to file provided and signal core keep this turn.
        saveCore(action.at(1));
        control = Control::SAME;
    } else if (type == "quit") {
        control = Control::QUIT;
    }
}

void Core::handlePlace(Player &player, const std::vector<std::string> &action) {
    control = Control::INVALID;
    if (action.size() == 2 && action.at(1) == "Done") {
        placeDone(player);
    } else if (action.size() == 4 
        && action.at(2) == "at" 
        && player.getHand()->contains(action.at(3).at(0))) {
        // If the args are correct and the hand contains letter to place.
        placeTile(player, action);
    }
}

void Core::placeDone(Player &player) {
    int handSize {player.getHand()->size()};
    // Replenish player's hand whilst there are still tiles in bag.
    while (bag->size() > 0 && handSize < HAND_SIZE) {
        player.getHand()->append(bag->pop());
        ++handSize;
    }
    // Signal core transition to next player.
    player.donePlacing();
    control = Control::NEXT;
}

void Core::placeTile(Player &player, const std::vector<std::string> &action) {
    control = Control::INVALID;
    int score {insertTile(action)};
    // If the player's action was valid.
    if (score != 0) {
        // Delete placed tile from player's hand and reset player state.
        std::shared_ptr<LinkedList> hand {player.getHand()};
        hand->remove(action.at(1).at(0));
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
    return board->placeTile(
        std::toupper(position.at(0)) - 65, std::stoi(position.substr(1)),
        static_cast<char>(std::toupper(action.at(1).at(0)))
    );
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
    std::cout << std::endl 
        << players.at(current).getName() << " it's your turn.\n";
    for (const auto &player : players) {
        std::cout 
            << "Score for " << player.getName()
            << ": " << player.getScore() << std::endl;
    }
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
    // Find and declare winner by checking player scores.
    auto victor { std::max_element(players.begin(), players.end(), 
        [](const Player &a, const Player &b) {
            return a.getScore() < b.getScore();
        })[0]
    };
    std::cout << "Player " << victor.getName() << " won!\n\n";
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

