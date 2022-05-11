#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include "Tile.h"
#include "SaveState.h"

#include <vector>
#include <memory>
#include <string>
#include <sstream>

class Board {

    // Board is a two-dimensional vector of tiles.
    const std::size_t size;
    std::vector<std::vector<Tile>> board;

public:

    // Boards can be constructed using size or save state.
    explicit Board(size_t = 15);
    explicit Board(const std::string&);
    Board(const Board&);
    // Board(const SaveState&); Useless I guess?
    ~Board() = default;

    std::size_t getSize() const;
    std::string toString() const;

    int placeTile(std::size_t, std::size_t, char);
};

#endif // ASSIGN2_BOARD_H
