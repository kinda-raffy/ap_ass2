#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include <vector>
#include <memory>

// Do not use namespaces in header files.

class Board {

    // Board is a unique pointer to vector of unique pointers to char vectors?
    std::unique_ptr<std::vector<std::unique_ptr<std::vector<char>>>> board;
    const size_t dimension;

public:

    // TODO: Construct a board object using string?

    Board(size_t);
    Board(const Board&);
    ~Board();
};

#endif // ASSIGN2_BOARD_H
