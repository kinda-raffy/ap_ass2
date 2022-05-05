#include "Board.h"

using std::vector;

Board::Board(size_t size)
    : size {size}, board {vector<vector<char>> {}} {
    for (size_t index {0}; index < size; ++index) {
        // Create row and initialise all positions to null.
        vector<char> row (size, '\0');
        board.push_back(row);
    }
}

Board::Board(const Board &source)
    : size {size}, board {vector<vector<char>> {}} {
    // Copy all characters into corresponding positions.
    for (size_t index{0}; index < size; ++index) {
        board.push_back(source.board.at(index));
    }
}
