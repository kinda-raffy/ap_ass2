#include "Board.h"

Board::Board(std::size_t size)
    : size {size}, board {std::vector<std::vector<Tile>> {}} {
    for (std::size_t index {0}; index < size; ++index) {
        // Create row and initialise all positions to null tiles.
        std::vector<Tile> row (size, Tile {'-'});
        board.push_back(row);
    }
}

// TODO: Finish this constructor.
Board::Board(const std::string &boardString)
    : size {}, board {} {
    
}

Board::Board(const Board &source)
    : size {source.size}, board {std::vector<std::vector<Tile>> {}} {
    // Copy all characters into corresponding positions.
    for (std::size_t index{0}; index < size; ++index) {
        board.push_back(source.board.at(index));
    }
}

std::size_t Board::getSize() const {
    return size;
}

// Create a string that visually represents the current board state.
std::string Board::toString() const {
    std::stringstream stream {};
    // Col indicies.
    stream << "  ";
    for (std::size_t index {0}; index < size; ++index) {
        stream << ((index > 10) ? " " : "  ") << index << " ";
    }
    stream << "\n";
    // Top border.
    stream << "  ";
    for (std::size_t index {0}; index < 4 * size + 1; ++index) {
        stream << "-";
    }
    // Row labels and body.
    stream << std::endl;
    char rowLabel {'A'};
    // Iterate over each space in the vector.
    for (const std::vector<Tile> &row : board) {
        stream << rowLabel++ << " | ";
        for (const Tile &position : row) {
            // Convert unused tiles into spaces for printing.
            char letter {position.getLetter()};
            stream << ((letter != '-') ? letter : ' ') << " | ";
        }
        stream << std::endl;
    }
    return stream.str();
}

int Board::placeTile(std::size_t x, std::size_t y, char letter) {
    int placeValue = 0;
    // Size types are unsigned, so only upper bound checking required.
    if (x < size && y < size) {
        bool null {board.at(x).at(y).getLetter() == '-'};
        if (null) {
            board.at(x).at(y).setLetter(letter);
            placeValue = board.at(x).at(y).getValue();
        }
    }
    return placeValue;
}
