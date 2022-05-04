#include <iostream>
#include "Board.h"

using std::make_unique, std::unique_ptr, std::vector;

Board::Board(size_t dimension)
    : board {make_unique<vector<unique_ptr<vector<char>>>>()},
    dimension {dimension} {
    // TODO: Test all of this.
    for (size_t index {0}; index < dimension; ++index) {
        board->emplace_back(make_unique<vector<char>>());
    }
}

Board::Board(const Board &source)
    : Board {source.dimension} {
    // TODO: Figure out how this will be done.
}

Board::~Board() = default;
