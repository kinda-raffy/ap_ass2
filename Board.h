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

    /**
     * @brief Construct a square Board of the given size.
     *
     * @param size The size of the board to create (both dimensions).\n
     * default = 15
     */
    explicit Board(size_t = 15);

    /**
     * @brief Construct a board from a string representation.
     *
     * @param string The string to create the board from.\n
     * The format is the same as created by Board::toString()
     */
    explicit Board(const std::string &);

    /**
     * @brief Copy constructor, create a copy of given board.
     *
     * @param board The board to create a copy of.
     */
    Board(const Board &);

    ~Board() = default;

    /**
     * @brief Get the letter on the board at the given coordinates.
     *
     * @param x The x-coordinate to get the letter at.
     * @param y The y-coordinate to get the letter at.
     * @return The character at (x, y) on the board.\n
     * Returns '-' if the space is empty.
     */
    char getLetter(std::size_t, std::size_t) const;

    /**
     * @brief Get the side length of the board (which is always square).
     *
     * @return The side length of the board.
     */
    std::size_t getSize() const;

    /**
     * @brief Get the string representation of this board.
     *
     * @return String representing the state of this board. Example:\code
     *     0   1   2   3   4   5   6   7   8   9   10  11  12  13  14
     *   -------------------------------------------------------------
     * A |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     * B |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     * C |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     * D |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     * E |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     * F |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     * G |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     * H |   |   |   |   |   |   |   | C | A | T |   |   |   |   |   |
     * I |   |   |   |   |   |   |   |   |   | O |   |   |   |   |   |
     * J |   |   |   |   |   |   |   |   |   | Y |   |   |   |   |   |
     * K |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     * L |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     * M |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     * N |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     * O |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
     * \endcode
     */
    std::string toString() const;

    /**
     * @brief Place a tile at the given coordinates, given that placing a tile
     * there is valid.
     *
     * @param x The x-coordinate to place at.
     * @param y The y-coordinate to place at.
     * @param letter The letter to place.
     * @return If the place is valid, the point value of letter. If the place is
     * invalid, 0.
     */
    int placeTile(std::size_t, std::size_t, char);

    /**
     * @brief Check if the string provided is a valid board.
     *
     * @param lines A vector containing each line of the board.
     * @return True if the board is valid, false otherwise.
     */
    static bool validateBoardString(const std::vector<std::string> &);

    /**
     * @brief Check if the string provided is a valid board.
     *
     * @param lines A vector containing each line of the board.
     * @param lo The index of the first line of the board.
     * @param hi The index of the second line of the board.
     * @return True if the board is valid, false otherwise.
     */
    static bool validateBoardString(const std::vector<std::string> &,
                                    std::size_t, std::size_t);
};

#endif // ASSIGN2_BOARD_H
