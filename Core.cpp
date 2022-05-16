#include "Core.h"

void Core::printDuck() {
    std::cout << "https://imgur.com/gallery/w9Mjo4y" << std::endl;
}

Core::Core(const std::vector<std::string> &players) 
    : bag {std::move(Core::createBag())}, board {std::make_shared<Board>()}, 
      current {0} {
    for (const std::string &name : players) {
        this->players.emplace_back(name, bag);
    }
}

Core::Core(SaveState &save) 
    : bag {std::make_shared<LinkedList>(save.getTiles())},
      board {std::make_shared<Board>(save.getBoard())}, 
      current {save.getCurrent()} {
    // Create player objects using save state strings.
    std::shared_ptr<std::vector<std::string>> names {save.getPlayers()},
        hands {save.getHands()};
    std::shared_ptr<std::vector<int>> scores {save.getScores()};
    std::size_t index {0}, bound {names->size()};
    while (index < bound) {
        Player player {names->at(index), hands->at(index), scores->at(index)};
        players.emplace_back(player);
        ++index;
    }
}

void Core::changeTurn() {
    current = (current >= players.size() - 1) ? 0 : current + 1;
}

// TODO: This is the last function that probably needs to be clearer.
void Core::runCore() {
    int coreControl {NEXT_PLAYER};
    do {
        if (coreControl != INVALID_ACT && coreControl != SAME_PLAYER) {
            displayTurn();
        } else if (coreControl == INVALID_ACT) {
            std::cout << "Invalid Input" << std::endl;
        }

        std::string word {}, input {};
        std::vector<std::string> action {};
        // Process user's selected action into a vector of strings.
        std::cout << "> " << std::flush;
        std::getline(std::cin >> std::ws, input);
        if (!std::cin.eof()) {
            std::istringstream stream {input};
            while (stream >> word) {
                action.emplace_back(word);
            }
        } else {
            action.emplace_back("quit");
        }
        if (action.empty()) {
            // If there is no action specified.
            coreControl = INVALID_ACT;
        } else if (players.at(current).getPass() >= 1) {
            // Cease if the player exceeds the pass bound.
            displayEnd();
            coreControl = QUIT;
        } else {
            // Perform action.
            coreControl = handleAction(action);
        }
        // Cease if there are no tiles left in bag or hands.
        if (!bag->size() && !players.at(current).getHand()->size()) {
            coreControl = QUIT;
        }
        // Update core state if either control is encountered.
        if (coreControl == QUIT) {
            displayEnd();
        }
        else if (coreControl == NEXT_PLAYER) {
            changeTurn();
        }
    } while (coreControl != QUIT);
    std::cout << "Goodbye" << std::endl;
}

// Save current core state to file.
void Core::saveCore(const std::string &file) {
    std::unique_ptr<SaveState> save {std::make_unique<SaveState>(*this)};
    save->saveToFile(file);
}

int Core::handleAction(const std::vector<std::string> &action) {
    const std::string type {action.at(0)};
    Player& player {players.at(current)};
    int state {INVALID_ACT};
    for (const auto &act : action) std::cout << act << std::endl;
    if (type == "place") {
        state = handlePlace(player, action);
    } else if (type == "replace" && !player.isPlacing()) {
        state = replaceTile(player, action);
    } else if (type == "pass" && !player.isPlacing()) {
        // Update player object pass count and signal core to next player.
        player.incrementPass();
        state = NEXT_PLAYER;
    } else if (type == "save" && action.size() == 2 && !player.isPlacing()) {
        // Save core state to file provided and signal core keep this turn.
        saveCore(action.at(1));
        state = SAME_PLAYER;
    } else if (type == "quit") {
        state = QUIT;
    }
    return state;
}

int Core::handlePlace(Player &player, const std::vector<std::string> &action) {
    int state {INVALID_ACT};
    if (action.size() == 2 && action.at(1) == "Done") {
        state = placeDone(player);
    } else if (action.size() == 4 && action.at(2) == "at") {
        state = placeTile(player, action);
    }
    return state;
}

int Core::placeDone(Player &player) {
    int handSize {player.getHand()->size()};
    // Replenish player's hand whilst there are still tiles in bag.
    while (bag->size() > 0 && handSize < HAND_SIZE) {
        player.getHand()->append(bag->pop());
        ++handSize;
    }
    // Signal core transition to next player.
    player.donePlacing();
    return NEXT_PLAYER;
}

int Core::placeTile(Player &player, const std::vector<std::string> &action) {
    int state {INVALID_ACT};
    int value {insertTile(action)};
    // If the player's action was valid.
    if (value != 0) {
        // Delete placed tile from player's hand and reset player state.
        std::shared_ptr<LinkedList> hand {player.getHand()};
        hand->remove(action.at(1).at(0));
        player.refreshPass();
        player.startPlacing();
        // Calculate the score, including checking for bingo.
        if (hand->size() == 0) {
            std::cout << "\nBINGO!!!\n\n";
            value += BINGO_BONUS;
        }
        // Add score to player object, and signal core to stay on turn.
        player.addScore(value);
        state = SAME_PLAYER;
    }
    return state;
}

int Core::insertTile(const std::vector<std::string> &action) {
    std::string position {action.at(3)};
    return board->placeTile(
        std::toupper(position.at(0)) - 65, std::stoi(position.substr(1)),
        static_cast<char>(std::toupper(action.at(1).at(0)))
    );
}

int Core::replaceTile(Player &player, const std::vector<std::string> &action) {
    int state {INVALID_ACT};
    player.refreshPass();
    // Get replace character and check for valid input.
    std::string letter {action.at(1)};
    if (letter.size() == 1 
        && player.getHand()->replace(letter.at(0), bag->pop())) {
        // If valid and replaced tile in hand, put exchanged tile in bag.
        bag->append(letter.at(0));
        state = NEXT_PLAYER;
    }
    return state;
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
    for (const auto& player : players) {
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
    for (auto& player : players) {
        std::cout 
            << "Score for " << player.getName() 
            << ": " << player.getScore() << std::endl;
    }
    // Find and declare winner by checking player scores.
    auto victor { std::max_element(players.begin(), players.end(), 
        [](const Player& a, const Player& b) {
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

