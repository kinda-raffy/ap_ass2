#include "Board.h"

Board::Board(size_t dimension)
    : dimension {dimension}, 
    board {std::vector<std::vector<char>> {}} {
    // TODO: Finish implementation; emptry positions.
    for (size_t index {0}; index < dimension; ++index) {
        board.emplace_back(std::vector<char> {});
    }
}

Board::Board(const Board &source)
    : Board {source.dimension} {
    // Copy all characters into corresponding positions.
    int row {0};
    while (row < dimension) {
        int col {0};
        while (col < dimension) {
            board.at(row).at(col) = source.board.at(row).at(col);
            ++col;
        }
        ++row;
    }
}
