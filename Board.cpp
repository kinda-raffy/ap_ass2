#include "Board.h"

using std::make_unique, std::unique_ptr, std::vector;

Board::Board(size_t rows, size_t cols)
    : rows {rows}, cols {cols}, 
    board {make_unique<vector<unique_ptr<vector<char>>>>()} {
    // TODO: Test all of this.
    for (size_t index {0}; index < rows; ++index) {
        board->emplace_back(make_unique<vector<char>>());
    }
}

Board::Board(const Board &source)
    : rows {source.rows}, cols {source.cols} {
    // TODO: Figure out how this will be done.
}
