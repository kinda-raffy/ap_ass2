#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <map>
#include <cctype>

class Tile {

    char letter;

public:

    /**
     * @brief Create a tile with the given letter.
     *
     * @param letter The letter this tile will contain.
     */
    explicit Tile(char);

    /**
     * @brief Create a copy of the given tile.
     *
     * @param tile The tile to create a copy of.
     */
    Tile(const Tile &);

    ~Tile() = default;

    /**
     * @brief Get the point value of the tile.
     *
     * @return The point value associated with the letter of this tile.
     */
    int getValue() const;

    /**
     * @brief Get the letter of this tile.
     *
     * @return A char representing the letter of this tile.
     */
    char getLetter() const;

    /**
     * @brief Set the letter of this tile.
     * Throws exception if letter is invalid.
     *
     * @param letter The char to set.
     */
    void setLetter(char);

    /**
     * @brief Gets the point value of the letter passed in.
     *
     * @param letter The letter to get a point value of.
     * @return The point value of letter in scrabble.
     */
    static int getTileValue(char);
};

#endif // ASSIGN2_TILE_H
