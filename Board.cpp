#include "Board.h"

Board::Board(std::size_t size)
    : size {size}, board {std::vector<std::vector<Tile>> {}} {
    for (std::size_t index {0}; index < size; ++index) {
        // Create row and initialise all positions to null tiles.
        std::vector<Tile> row (size, Tile {'\0'});
        board.push_back(row);
    }
}

Board::Board(const Board &source)
    : size {size}, board {std::vector<std::vector<Tile>> {}} {
    // Copy all characters into corresponding positions.
    for (std::size_t index{0}; index < size; ++index) {
        board.push_back(source.board.at(index));
    }
}

std::size_t Board::getSize() const {
    return size;
}

// Convert current board into a save state string.
std::string Board::toSave() const {
    std::stringstream stream {};
    // Push board size to string stream.
    stream << size << ' ';
    for (const std::vector<Tile> &row : board) {
        for (const Tile &position : row) {
            stream << position.getLetter();
        }
    }
    return stream.str();
}
