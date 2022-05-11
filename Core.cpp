#include "Core.h"

#include <utility>

void Core::printDuck() {
    std::cout << "https://imgur.com/gallery/w9Mjo4y" << std::endl;
}

Core::Core(std::vector<std::string> playerNames) {
    // New game constructor.
    this->bag = std::move(createNewBag());
    this->players = createPlayers(std::move(playerNames));
    this->board = std::make_shared<Board>(Board());
    this->current = 0;
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
    std::cout << "\nGame over" << std::endl;
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
    const std::string act {actVec[0]};

    // Place a tile.
    if (act == "place") {
        players.at(current).refreshPass();
        if (actVec.size() == 2 && actVec[1] == "Done") {
            // Replenish hand if bag is not empty.
            while (bag->size() != 0 &&
                   players.at(current).getHand()->size() < HAND_SIZE) {
                players.at(current).getHand()->append(bag->pop());
            }
            retStat = NEXT_PLAYER;
        } else if (actVec.size() == 4) {
            // Command | place <letter> at <pos>
            char letter = std::toupper(actVec[1][0]);

            // Check if letter is in hand.
            if (players.at(current).getHand()->contains(letter)) {
                std::string pos = actVec[3];

                // Convert pos to (x, y) coordinates
                int posX = int(pos[0]) - 65;  // i'm sorry TODO make less bad
                int posY = std::stoi(pos.substr(1));
                // TODO: check if remainder of pos is actually
                // an int before doing that

                // Place tile
                int value = board->placeTile(posX, posY, letter);
                int valid = value;

                // If move was valid, remove tile from player hand
                if (valid) {
                    players.at(current).getHand()->remove(letter);
                }

                // Check for bingo, will be true if player's hand is now empty
                bool bingo = false;
                if (players.at(current).getHand()->size() == 0) {
                    bingo = true;
                }

                if (valid) {
                    // Increase score.
                    if (bingo) {
                        std::cout << "\nBINGO!!!\n" << std::endl;
                        players.at(current).addScore(value + BINGO_BONUS);
                    } else {
                        players.at(current).addScore(value);
                    }
                    retStat = SAME_PLAYER;
                } else {
                    // Illegal move.
                    retStat = INVALID_ACT;
                }
            } else {
                // Letter is not in player's hand.
                retStat = INVALID_ACT;
            }
        } else {
            // Vector is of insufficient length.
            retStat = INVALID_ACT;
        }
    }
    // Replace a single tile on the player's hand.
    else if (act == "replace" && actVec.size() == 2) {
        players.at(current).refreshPass();
        // Command | replace <repLetter>.
        std::string repLetter = actVec[1];

        if (repLetter.length() != 1) {
            //  Replacement letter not a char.
            retStat = INVALID_ACT;
        }
        // Replace letter on hand.
        else if (!(players.at(current).getHand()
                ->replace(repLetter[0], bag->pop()))) {
            // Tile to be replaced is not in hand.
            retStat = INVALID_ACT;
        }
        else {
            // On successful replacement, add the old letter to the tile bag.
            bag->append(repLetter[0]);
            retStat = NEXT_PLAYER;
        }
    }
    // Don't play this round. Maximum 2 consecutive passes allowed.
    else if (act == "pass" && actVec.size() == 1) {
        players.at(current).incrementPass();
        retStat = NEXT_PLAYER;
    }
    // Saves game.
    else if (act == "save" && actVec.size() == 2) {
        // Command | save <filename>
        saveGame(actVec[1]);
        retStat = SAME_PLAYER;
    }
    // Quit game. Does not show game end dialogue.
    else if (act == "quit" && actVec.size() == 1) {
        retStat = QUIT;
    }
    // Invalid command.
    else {
        // Command is not part of spec.
        retStat = INVALID_ACT;
    }
    return retStat;
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
    std::cout << '\n'
              << players.at(current).getName()
              << " it's your turn." << std::endl;
    for (auto& _p : players) {
        std::cout << "Score for " << _p.getName()
                  << ": " << _p.getScore() << std::endl;
    }
    std::cout << board->toString() << "\n\n"
              << "Your hand is\n"
              << players.at(current).handToString() << '\n'
              << std::endl;
}

void Core::runGame() {
    // TODO - Perform preliminary checks before starting core.
    int coreControl{NEXT_PLAYER};

    // Run round.
    do {
        if (coreControl != INVALID_ACT && coreControl != SAME_PLAYER)
            displayTurn();

        std::string word;
        std::string actionLine;
        std::vector<std::string> actionList;

        // Get game action as a vector of strings.
        std::cout << "> " << std::flush;
        std::getline(std::cin >> std::ws, actionLine);
        if (std::cin.eof()) {
            actionList.emplace_back("quit");
        } else {
            std::istringstream iss(actionLine);
            while (iss >> word)
                actionList.emplace_back(word);
        }

        // Perform preliminary checks then action.
        if (actionList.empty()) {
            // There is no action.
            coreControl = INVALID_ACT;
        } else if (players.at(current).getPass() >= 1) {
            // End game if player exceeded pass limit.
            displayEnd();
            coreControl = QUIT;
        } else {
            // Perform action.
            coreControl = handleAction(actionList);
        }

        // Handle Core Control.
        if (coreControl == INVALID_ACT) {
            std::cout << "\nInvalid input.\n" << std::endl;
        } else if (coreControl == NEXT_PLAYER) {
            changeTurn();
        }

        // The below conditional carries greater precedence over core control.
        // Tile bag is empty and current's hand is empty.
        if (!bag->size() && !players.at(current).getHand()->size()) {
            displayEnd();
            coreControl = QUIT;
        }
    } while (coreControl != QUIT);
    std::cout << "Goodbye" << std::endl;
}


// Save current game state to file using the given file name.
void Core::saveGame(const std::string &file) {
    std::unique_ptr<SaveState> save {std::make_unique<SaveState>(*this)};
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
