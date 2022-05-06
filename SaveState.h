#ifndef ASSIGN2_SAVE_STATE_H
#define ASSIGN2_SAVE_STATE_H

//#include "Core.h"
#include "Board.h"
#include "Player.h"

#include <string>
#include <fstream>
#include <vector>
#include <memory>

class SaveState {

    std::string tiles;
    std::string board; // Regex could be used for validation if required? 

    std::vector<const std::string> players;
    std::vector<const std::string> hands;
    std::vector<const int> scores;
    int current;

public:

    // TODO: Copy constructor?

    SaveState(const std::string&, std::size_t = 2, std::size_t = 15);
    SaveState(const Core&);
    ~SaveState() = default;
    // SaveState(const Board&, const std::vector<Player>&, const LinkedList&, const int); Backup process.

    void saveToFile(const std::string&) const;
};

#endif // ASSIGN2_SAVE_STATE_H
