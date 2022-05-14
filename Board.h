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
    std::size_t size;
    std::vector<std::vector<Tile>> board;

public:

    // Boards can be constructed using size or string representation.
    explicit Board(size_t = 15);
    explicit Board(const std::string&);
    Board(const Board&);
    ~Board() = default;

    std::size_t getSize() const;
    std::string toString() const;

    int placeTile(std::size_t, std::size_t, char);

    
    static bool validateBoardString(const std::string&);
    static bool validateBoardString(const std::vector<std::string>&);
};

#endif // ASSIGN2_BOARD_H
