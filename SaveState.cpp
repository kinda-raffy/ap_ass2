#include "SaveState.h"
#include "Core.h"

// Create a save state using text file. Auto deduces players and board size.
SaveState::SaveState(const std::string &input) {
    // Use input string to locate save state file and read.
    std::ifstream file {input};
    if (!file) {
        std::cout << "Error accessing file. Object invalid." << std::endl;
    } else {
        // Collect all lines from file first.
        std::vector<std::string> lines {};
        std::string line {};
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        // Subtract last two lines containing bag and current player.
        std::size_t size {lines.size() - 2};
        std::size_t partition {0};
        // Partition should index the first line of the board.
        while (lines.at(partition).at(0) != ' ') {
            ++partition;
        }
        // Find the player count by dividing leading line count by three.
        const std::size_t playerCount {(partition - 1) / 3};
        /* 
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
        */
        std::size_t index {0};
        // Read and store player data. Index tracks position in vector.
        for (std::size_t player {0}; player < playerCount; ++player) {
            players.push_back(lines.at(index++));
            scores.push_back(std::stoi(lines.at(index++)));
            hands.push_back(lines.at(index++));
        }
        // Read board string beginning at partition index.
        for (; partition < size; ++partition) {
            board += lines.at(partition) + "\n";
        }
        // Read tile bag and current player data.
        tiles = lines.at(size++); 
        const std::string currentPlayer {lines.at(size)};
        current = 0;
        while (players.at(current) != currentPlayer) {
            ++current;
        }
    }
}

// FIXME: Once Core is finalised fix this constructor.
SaveState::SaveState(Core &core) :
    tiles {core.getBag()->toString()}, board {core.getBoard()->toString()},
    players {}, hands {}, scores {}, current {core.getCurrent()}  {
    // Iteratively convert all player info into save strings and store.
    std::shared_ptr<std::vector<Player>> corePlayers {core.getPlayers()};
    for (const Player player : *corePlayers) {
        players.push_back(player.getName());
        scores.push_back(player.getScore());
        hands.push_back(player.handToString());
    }
}

// TODO: Test to verify that this works as intended.
void SaveState::saveToFile(const std::string &location) const {
    std::ofstream out {location};
    // If the output file was successfully opened, then write contents.
    if (out) {
        std::size_t index {0};
        while (index < players.size()) {
            out << players.at(index) << std::endl
                << scores.at(index) << std::endl
                << hands.at(index) << std::endl;
            ++index;
        }
        out << board << tiles << std::endl << players.at(current) << std::endl;
    }
    // Close the output file stream once all contents have been transferred.
    out.close();
    std::cout << "\nGame successfully saved\n" << std::endl;
}
