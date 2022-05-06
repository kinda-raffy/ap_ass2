#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include "Tile.h"
#include "SaveState.h"

#include <vector>
#include <memory>
#include <string>
#include <sstream>

class Board {

    // Board is a two dimensional vector of tiles.
    const size_t size;
    std::vector<std::vector<Tile>> board;

public:

    // Boards can be constructed using size or save state.
    explicit Board(size_t);
    explicit Board(const std::string&);
    Board(const Board&);
    // Board(const SaveState&); Useless I guess?
    ~Board() = default;

    std::size_t getSize() const;
    std::string toString() const;
};

#endif // ASSIGN2_BOARD_H
