#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include <vector>
#include <memory>

// Do not use namespaces in header files.

class Board {

    // Board is a two dimensional vector of characters.
    std::vector<std::vector<char>> board;
    const size_t dimension;

public:

    // TODO: Construct a board object using string?
    explicit Board(size_t);
    Board(const Board&);
    ~Board();
};

#endif // ASSIGN2_BOARD_H
