#ifndef ASSIGN2_SAVE_STATE_H
#define ASSIGN2_SAVE_STATE_H

#include "Core.h"
#include "Board.h"
#include "Player.h"

#include <string>
#include <fstream>
#include <vector>

class SaveState {

    const std::string tiles;
    const std::string board; // Regex could be used for validation.
    std::size_t partition;

    std::vector<const std::string> players;
    std::vector<const std::string> hands;
    std::vector<const int> scores;
    
    int current;

public:

    // SaveState(const std::ifstream&); ?
    SaveState(const Core&);
    SaveState(const Board&, const std::vector<Player>&, const LinkedList&, const int);
    SaveState(const SaveState&);

    std::size_t getSize() const;
    std::string getLetters() const;
    void saveToFile(const std::string&) const;
};

#endif // ASSIGN2_SAVE_STATE_H
