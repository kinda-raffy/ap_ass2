#include "SaveState.h"

SaveState::SaveState(const Core &core) : 
    board {core.board->toString()},
    tiles {core.tiles->toString()},
    partition {this->board.find(' ')}, 
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

// TODO: Fix for deep copy.
SaveState::SaveState(const SaveState &save) : 
    board     {save.board}, 
    tiles     {save.tiles},
    players   {save.players},
    scores    {save.scores},
    hands     {save.hands},
    current   {save.current},
    partition {save.partition} {
}

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
