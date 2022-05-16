#include "SaveState.h"
#include "Core.h"

// Create a save state using text file. Auto deduces players and board size.
SaveState::SaveState(const std::string &input) {
    std::vector<std::string> lines {};
    SaveState::readSaveFile(input, lines);
    try {
        if (!SaveState::validateSaveString(lines)) {
            throw std::runtime_error("Incorrect format in save file.");
        }
        // Up until last two lines containing bag and current player.
        std::size_t size {lines.size() - 2};
        // Partition should index the first board line. Assume min two players.
        std::size_t partition {6};
        while (lines.at(partition).at(0) != ' ') {
            ++partition;
        }
        // Read and store player data until board section reached.
        for (std::size_t index {0}; index < partition;) {
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
        std::cout << "Scrabble game successfully loaded" << std::endl;
    } catch (std::runtime_error &re) {
        std::cout << re.what() << std::endl;
    }
}

SaveState::SaveState(Core &core) 
    : tiles {core.getBag()->toString()}, board {core.getBoard()->toString()},
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
        std::cout << "\nGame successfully saved\n" << std::endl;
    } else {
        std::cout << "Invalid file specification." << std::endl;
    }
    // Close the output file stream once all contents have been transferred.
    out.close();
}

std::string& SaveState::getTiles() {
    return tiles;
}

std::string& SaveState::getBoard() {
    return board;
}

std::shared_ptr<std::vector<std::string>> SaveState::getPlayers() {
    return std::make_shared<std::vector<std::string>>(players);
}   

std::shared_ptr<std::vector<std::string>> SaveState::getHands() {
    return std::make_shared<std::vector<std::string>>(hands);
}

std::shared_ptr<std::vector<int>> SaveState::getScores() {
    return std::make_shared<std::vector<int>>(scores);
}

std::size_t SaveState::getCurrent() {
    return current;
}

void SaveState::readSaveFile(const std::string &input, 
    std::vector<std::string> &lines) {

    // Use input string to locate save state file and read.
    std::ifstream file {input};
    try {
        if (!file) {
            throw std::runtime_error("Save file cannot be opened.");
        } else {
            // Collect all lines and read into vector.
            std::string line {};
            while (std::getline(file, line)) {
                lines.emplace_back(line);
            }
        }
    } catch (std::runtime_error &re) {
        std::cout << re.what() << std::endl;
    }
}

bool SaveState::validateSaveString(const std::vector<std::string> &save) {
    bool correct {true};
    std::size_t index {0};
    // Validate all player data. Name should be all charcters, score digits.
    while (save.at(index).at(0) != ' ' && correct) {
        correct = correct && Player::validatePlayerStrings(save, index);
        index += 3;
    }
    // Validate board and tile bag data.
    correct = correct && 
        Board::validateBoardString(save, index, save.size() - 2);
    /* 
        std::vector<std::string> board {};
        while (index < save.size() - 2) {
            board.push_back(save.at(index++));
        }
        Board::validateBoardString(board);
    */
    correct = correct && LinkedList::validateListString(save.at(index++));
    correct = correct && std::regex_match(save.at(index), std::regex("[A-Z]+"));
    return correct;
}
