#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include <regex>
#include <array>
#include <vector>
#include <memory>
#include <string>
#include <sstream>

class Tile;

class Board {

    // Board is a two-dimensional vector of tiles.
    std::size_t size;
    std::vector<std::vector<Tile>> board;

    bool empty;

public:

    // Boards can be constructed using size or string representation.
    explicit Board(size_t = 15);
    explicit Board(const std::string&);
    Board(const Board&);
    ~Board() = default;

    char getLetter(std::size_t, std::size_t) const;
    std::size_t getSize() const;
    std::string toString() const;

    int placeTile(std::size_t, std::size_t, char);

    static bool validateBoardString(const std::vector<std::string>&);
    static bool validateBoardString(const std::vector<std::string>&, 
        std::size_t, std::size_t);
};

#endif // ASSIGN2_BOARD_H
