#ifndef ASSIGN2_SAVE_STATE_H
#define ASSIGN2_SAVE_STATE_H

#include "Board.h"

#include <string>

class SaveState {

    // Should probably have regex for validation.
    const std::string save;
    const std::size_t partition;

    // TODO: Read player hands.

public:

    // SaveState(const std::ifstream&); ?
    SaveState(const std::string&);
    SaveState(const SaveState&);

    std::size_t getSize() const;
    std::string getLetters() const;
};

#endif // ASSIGN2_SAVE_STATE_H
