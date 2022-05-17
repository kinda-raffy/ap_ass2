#include "Board.h"
#include "Tile.h"
#include "SaveState.h"

Board::Board(std::size_t size)
    : size {size}, board {std::vector<std::vector<Tile>> {}}, empty {true} {
    for (std::size_t index {0}; index < size; ++index) {
        // Create row and initialise all positions to null tiles.
        std::vector<Tile> row(size, Tile {'-'});
        board.push_back(row);
    }
}

// FIXME: Delete debug print when verified.
Board::Board(const std::string &state)
    : size {0}, board {}, empty {true} {
    std::istringstream input {state};
    std::string line {};
    // Skip the first two lines. Better way to do this?
    for (std::size_t skip {0}; skip < 2; ++skip) {
        std::getline(input, line);
    }
    // Extract characters for each line of the state string.
    while (std::getline(input, line)) {
        std::vector<Tile> row {};
        board.push_back(row);
        // Characters always begin at the fifth position. Always four apart.
        std::size_t index {4};
        while (index < line.size()) {
            // Create tile for each character and point index to next position.
            char letter = line.at(index);
            empty = empty && letter != ' ';
            Tile tile {(letter == ' ') ? '-' : letter};
            board.at(size).push_back(tile);
            index += 4;
        }
        ++size;
    }
}

Board::Board(const Board &source)
    : size {source.size}, board {std::vector<std::vector<Tile>> {}} {
    // Copy all characters into corresponding positions.
    for (std::size_t index{0}; index < size; ++index) {
        board.push_back(source.board.at(index));
    }
}

char Board::getLetter(std::size_t x, std::size_t y) const {
    return (x < size && y < size) ? board.at(x).at(y).getLetter() : '-';
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
        stream << '\n';
    }
    // Remove the last newline.
    stream.seekp(-1, std::ios_base::end);
    return stream.str();
}

int Board::placeTile(std::size_t x, std::size_t y, char letter) {
    int value {0};
    // Size types are unsigned, so only upper bound checking required.
    if (x < size && y < size) {
        bool adjacent {empty};
        if (!empty) {
            const std::array<int, 4> sign {1, -1, 0, 0};
            std::size_t length {sign.size()};
            for (std::size_t lo {0}, hi {length - 1}; lo < length; ++lo, --hi) {
                std::size_t row {x + sign.at(lo)}, col {y + sign.at(hi)};
                if (row < size && col < size) {
                    adjacent = adjacent 
                        || board.at(row).at(col).getLetter() != '-';
                }
            }
        }
        if (adjacent && board.at(x).at(y).getLetter() == '-') {
            board.at(x).at(y).setLetter(letter);
            value = Tile::getTileValue(letter);
            empty = false;
        }
    }
    return value;
}

bool Board::validateBoardString(const std::vector<std::string> &lines) {
    std::size_t lo {0}, hi {lines.size() - 2};
    while (lines.at(lo).at(0) != ' ') {
        ++lo;
    }
    return Board::validateBoardString(lines, lo, hi);
}

// TODO: Fix pattern regex? Or hope it isn't noticed.
bool Board::validateBoardString(const std::vector<std::string> &lines, 
    std::size_t lo, std::size_t hi) {
    
    bool correct {true};
    // Verify header lines individually.
    correct = std::regex_match(lines.at(lo++),
        std::regex("( {2,4}[0-9]{1,2})+[ ]+"));
    correct = std::regex_match(lines.at(lo++), std::regex("  -+")) && correct;
    // Verify all lines used to represent board sequentially.
    const std::regex pattern {"[A-Z]{1}( | [A-Z ])+(.*)"};
    while (correct && lo < hi) {
        correct = std::regex_match(lines.at(lo++), pattern);
    }
    return correct;
}
