#include "Core.h"

#include <utility>

void Core::printDuck() {
    std::cout << "https://imgur.com/gallery/w9Mjo4y" << std::endl;
}

Core::Core(std::vector<std::string> playerNames) {
    // New game.
    this->bag = std::move(createNewBag());
    this->players = createPlayers(std::move(playerNames));
    this->board = std::make_shared<Board>(Board());
    this->current = 0;
}

Core::Core(const SaveState&) {
    // Load game.
    // FIXME - Extract state from SaveState.
}

std::vector<Player> Core::createPlayers(const std::vector<std::string> playerNames) {
    // Check if bag is nullptr.
    if (bag == nullptr) throw std::runtime_error("Bag is nullptr.");
    // Generate num of players with corresponding names.
    std::size_t numPlayers = playerNames.size();
    std::vector<Player> _players;
    _players.reserve(numPlayers);
    for (std::size_t i {0}; i < numPlayers; i++) {
        _players.emplace_back(Player(playerNames[i], bag));
    } return _players;
}

void Core::displayEnd() {
    std::cout << "Game over" << std::endl;
    // Scoreboard.
    for (auto& player : players) {
        std::cout << "Score for " << player.getName() << ": "
                                  << player.getScore() << std::endl;
    }
    // Declare winner.
    auto winner {
        std::max_element(players.begin(), players.end(), 
            [](const Player& a, const Player& b) {
                return a.getScore() < b.getScore();
            })[0]
    };
    std::cout << "Player " << winner.getName() << " won!\n" << std::endl;
}

void Core::changeTurn() {
    if (current >= static_cast<int>(players.size() - 1)) {
        this->current = 0;
    } else {
        this->current++;
    }
}

int Core::handleAction(std::vector<std::string> actVec) {
    int retStat {SAME_PLAYER};
    const std::string act = actVec[0];

    // Place a tile.
    if (act == "place") {
        players[current].refreshPass();
        if (actVec[1] == "Done") {
            // Replenish hand if bag is not empty.
            while (bag->size() != 0 &&
                   players[current].getHand()->size() < HAND_SIZE) {
                players[current].getHand()->append(bag->pop());
            }
            retStat = NEXT_PLAYER;
        } else {
            // Command | place <letter> at <pos>
            char letter = std::toupper(actVec[1][0]);
            std::string pos = actVec[3];

            // Convert pos to (x, y) coordinates
            int posX = int(pos[0]) - 65;  // i'm sorry TODO make less bad
            int posY = std::stoi(pos.substr(1));
            // TODO: check if remainder of pos is actually
            // an int before doing that

            // Place tile
            int value = board->placeTile(posX, posY, letter);

            // If move was valid, remove tile from player hand
            if (value) {
                players[current].getHand()->remove(letter);
            }

            // Check for bingo, will be true if player's hand is now empty
            bool bingo = false;
            if (players[current].getHand()->size() == 0) {
                bingo = true;
            }

            if (value) {
                // Increase score.
                if (bingo) {
                    std::cout << "\nBINGO!!!\n" << std::endl;
                    players[current].addScore(value + BINGO_BONUS);
                } else {
                    players[current].addScore(value);
                }
                retStat = SAME_PLAYER;
            } else {
                std::cout << "Illegal move." << std::endl;
                retStat = INVALID_ACT;
            }
        }
    }
    // Replace a single tile on the player's hand.
    else if (act == "replace") {
        players[current].refreshPass();
        // Command | replace <repLetter>.
        std::string repLetter = actVec[1];

        if (repLetter.length() != 1) {
            std::cout << "Replacement character is not a char." << std::endl;
            retStat = INVALID_ACT;
        }
        // Replace letter on hand.
        // FIXME - Simplify.
        else if (!(players[current].getHand()->replaceFirstInstance(repLetter[0], bag->pop()))) {
            std:: cout << "Tile " + repLetter + " not found in player's hand." << std::endl;
            retStat = INVALID_ACT;
        }
        // On successful replacement, add the old letter to the tile bag.
        else {
            bag->append(repLetter[0]);
            retStat = NEXT_PLAYER;
        }
    }
    // Don't play this round. Maximum 2 consecutive passes allowed.
    else if (act == "pass") {
        players[current].incrementPass();
        retStat = NEXT_PLAYER;
    }
    // Saves game.
    else if (act == "save") {
        // Command | save <filename>
        saveGame(actVec[1]);
        retStat = SAME_PLAYER;
    }
    // Quit game. Does not show game end dialogue.
    else if (act == "quit") {
        retStat = QUIT;
    }
    // Invalid command.
    else {
        std::cout << "Invalid Input." << std::endl;
        retStat = INVALID_ACT;
    } return retStat;
}


// TODO - Keep one or the other. Determine this in testing.
std::ostream &operator<<(std::ostream &os, const Core &core) {
    os << core.players[core.current].getName()
       << " it's your turn.\n";
    for (auto& _p : core.players) {
        os << "Score for " << _p.getName()
                  << ": " << _p.getScore() << '\n';
    }
    os << core.board->toString() << '\n';
    os << core.players.at(core.current).handToString() << '\n';
    return os;
}

/**
 * @brief Displays game at the start of every turn.
 * @order_of_ops Current name, Score of all players, Board, Current player hand.
 */
void Core::displayTurn() {
    std::cout << players.at(current).getName()
              << " it's your turn." << std::endl;
    for (auto& _p : players) {
        std::cout << "Score for " << _p.getName()
                  << ": " << _p.getScore() << std::endl;
    }
    std::cout << board->toString() << std::endl;
    std::cout << players.at(current).handToString() << std::endl;
}

void Core::runGame() {
    // TODO - Perform preliminary checks before starting core.
    int coreControl {SAME_PLAYER};

    // Run round.
    do {
        if (coreControl != INVALID_ACT)
            displayTurn();

        // Get game action.
        std::string word;
        std::string actionLine;
        std::vector<std::string> actionList;

        // Transform line into vector of words.
        std::cout << "> " << std::flush;
        std::getline(std::cin >> std::ws, actionLine);
        std::istringstream iss(actionLine);
        while (iss >> word)
            actionList.push_back(word);

        // Perform action.
        coreControl = handleAction(actionList);

        // Switch players.
        if (coreControl == NEXT_PLAYER)
            changeTurn();

        // The below conditionals carries greater precedence over core control.
        // Tile bag is empty and current's hand is empty.
        if (!bag->size() && !players.at(current).getHand()->size()) {
            displayEnd();
            coreControl = QUIT;
        }

        // If current player has passed twice.
        if (players[current].getPass() >= 2) {
            displayEnd();
            coreControl = QUIT;
        } // TODO: Simplify above.

    } while (coreControl != QUIT);
    std::cout << "Goodbye" << std::endl;
}

// Save current game state to file using the given file name.
void Core::saveGame(const std::string &file) const {
    std::unique_ptr<SaveState> save {std::make_unique<SaveState>(this)};
    save->saveToFile(file);
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

int Core::getCurrent() const {
    return current;
}
