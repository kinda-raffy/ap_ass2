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
    int current;

public:

    // TODO: Copy constructor?

    SaveState(const std::string&);
    SaveState(const Core&);
    ~SaveState() = default;
    // SaveState(const Board&, const std::vector<Player>&, const LinkedList&, const int); Backup process.

    void saveToFile(const std::string&) const;
};

#endif // ASSIGN2_SAVE_STATE_H
