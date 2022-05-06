#include "Board.h"

Board::Board(std::size_t size)
    : size {size}, board {std::vector<std::vector<Tile>> {}} {
    for (std::size_t index {0}; index < size; ++index) {
        // Create row and initialise all positions to null tiles.
        std::vector<Tile> row (size, Tile {'\0'});
        board.push_back(row);
    }
}

// TODO: Finish this constructor.
Board::Board(const std::string &save) 
    : board {}, size {} {
}

Board::Board(const Board &source)
    : size {source.size}, board {std::vector<std::vector<Tile>> {}} {
    // Copy all characters into corresponding positions.
    for (std::size_t index{0}; index < size; ++index) {
        board.push_back(source.board.at(index));
    }
}

/*
    Board::Board(const SaveState &saveState)
        : Board {saveState.getSize()} {
        std::string letters {saveState.getLetters()};
        std::size_t index {0};
        for (std::vector<Tile> &row : board) {
            for (Tile &position : row) {
                position.setLetter(letters.at(index++));
            }
        }
    }
*/

std::size_t Board::getSize() const {
    return size;
}

/*
    // Convert current board into a save state string.
    std::string Board::toString() const {
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
*/

// Create a string that visually represents the current board state.
std::string Board::toString() const {
    std::stringstream stream {};
    // Col indicies.
    stream << "  ";
    for (std::size_t index {0}; index < size; ++index) {
        stream << "  " << index << " ";
    }
    // Top border.
    stream << "  ";
    for (std::size_t index {0}; index < 3 * size; ++index) {
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
