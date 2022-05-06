#include "SaveState.h"

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

SaveState::SaveState(const SaveState &saveState)
    : board {saveState.board}, partition {saveState.partition} {
}

size_t SaveState::getSize() const {
    std::size_t size {0};
    if (partition != std::string::npos) {
        size = std::stoi(board.substr(0, partition));
    }
    return size;
}

std::string SaveState::getLetters() const {
    return board.substr(partition + 1);
}

// TODO: Output to file using correct format.
void SaveState::saveToFile(const std::string &location) const {
    std::ofstream outputFile {location, std::ios::trunc};
    // If the output file was successfully opened, then write contents.
    if (outputFile) {
    }
    // Close the output file stream once all contents have been transferred.
    outputFile.close();
}
