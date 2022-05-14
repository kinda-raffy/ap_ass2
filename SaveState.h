#ifndef ASSIGN2_SAVE_STATE_H
#define ASSIGN2_SAVE_STATE_H

#include "Board.h"
#include "Player.h"

#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>

// Forward declaration could fix yesterday's error.
class Core;

class SaveState {

    std::string tiles;
    std::string board; // Regex could be used for validation if required? 

    std::vector<std::string> players;
    std::vector<std::string> hands;
    std::vector<int> scores;
    std::size_t current;

public:

    SaveState(const std::string&);
    SaveState(Core&);
    ~SaveState() = default;

    void saveToFile(const std::string&) const;

    std::string& getTiles();
    std::string& getBoard();
    std::shared_ptr<std::vector<std::string>> getPlayers();    
    std::shared_ptr<std::vector<std::string>> getHands();
    std::shared_ptr<std::vector<int>> getScores();
    std::size_t getCurrent();

private:

    static std::unique_ptr<std::vector<std::string>> 
        readSaveFile(const std::string&);
    static bool validateSaveString(const std::vector<std::string>&);
};

#endif // ASSIGN2_SAVE_STATE_H
