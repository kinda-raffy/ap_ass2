#include "SaveState.h"



// Create a save state from text file. Refactor to auto find size args?
SaveState::SaveState(const std::string &input, 
    const std::size_t players, const std::size_t size) {
    // Use input string to locate save state file and read.
    std::ifstream file {input};
    if (!file) {
        std::cout << "Error accessing file. Object invalid." << std::endl;
    } else {
        std::string line;
        // Read player info.
        for (int index {0}; index < players; ++index) {
            std::getline(file, line);
            this->players.push_back(line);
            std::getline(file, line);
            scores.push_back(std::stoi(line));
            std::getline(file, line);
            hands.push_back(line);
        }
        // Read board info. Two lines added for header.
        for (int index {0}; index < size + 2; ++index) {
            std::getline(file, line);
            board += line + "\n";
        }
        // Tile bag and current player.
        std::getline(file, tiles);
        std::getline(file, line);
        current = 1;
        while (this->players.at(current - 1) != line) {
            ++current;
        }
    }
}

SaveState::SaveState(const Core &core) : 
    board {core.board->toString()},
    tiles {core.tiles->toString()},
    players {}, scores {}, hands {}, current {core.current}  {
    // Iteratively convert all player info into save strings and store.
    for (const Player &player : core.players) {
        players.push_back(player.getName());
        scores.push_back(player.getScore());
        hands.push_back(player.handToString());
    }
}

/*
    SaveState::SaveState(const Board &board, const std::vector<Player> &players, 
        const LinkedList& tiles, const int current) 
        : board {board.toString()}, tiles {tiles.toString()}, 
            partition {}, players {}, hands {}, scores {}, current {current} {
        partition = this->board.find(' ');
        for (const Player &player : players) {
            this->players.push_back(player.getName());
            this->scores.push_back(player.getScore());
            this->hands.push_back(player.handToString());
        }
    }
*/

void SaveState::saveToFile(const std::string &location) const {
    std::ofstream output {location, std::ios::trunc};
    // If the output file was successfully opened, then write contents.
    if (output) {
        std::size_t index {0}, bound {players.size()};
        while (index < bound) {
            output
                << players.at(index) << std::endl
                << scores.at(index)  << std::endl
                << hands.at(index)   << std::endl;
            ++index;
        }
        output 
            << board << std::endl 
            << tiles << std::endl
            << players.at(current - 1) << std::endl;
    }
    // Close the output file stream once all contents have been transferred.
    output.close();
}
