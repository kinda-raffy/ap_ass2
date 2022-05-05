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
    std::vector<std::vector<Tile>> board;
    const size_t size;

public:

    // Boards can be constructed using size or save state.
    explicit Board(size_t);
    Board(const SaveState&);
    Board(const Board&);
    ~Board() = default;

    std::size_t getSize() const;
    std::string toSave() const;
};

#endif // ASSIGN2_BOARD_H
