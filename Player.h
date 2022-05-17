#ifndef AP_ASS2_PLAYER_H
#define AP_ASS2_PLAYER_H

#define HAND_SIZE 7

#include <regex>
#include <string>
#include <vector>

// Tracks the colinearity of player's consecutive tile additions each turn.
enum Direction {
    X_AXIS,
    Y_AXIS,
    NONE
};

class LinkedList;

class Player {

    std::string name;
    std::shared_ptr<LinkedList> hand;
    int passes;
    int score;
    bool placing;

    // Place restrictions on actions in each individual turn.
    Direction direction;
    std::vector<std::string> turn;

public:

    /**
     * @brief Constructs a new player object with the given name and generates
     * a hand from the supplied tile bag linked list. All other fields default.
     */
    Player(const std::string&, std::shared_ptr<LinkedList>);

    /**
     * @brief Constructs a new player object with the given name and hand
     * represented as a linked list string. Integer represents player score.
     */
    Player(const std::string&, const std::string&, int);

    ~Player();

    // Standard getters and setters.
    std::string getName() const;
    int getScore() const;
    void setScore(int);
    void addScore(int);
    std::shared_ptr<LinkedList> getHand() const;

    /**
     * @brief Get the count of consecutive player passes.
     * @return int Number of consecutive passes.
     */
    int getPass() const;

    /**
     * @brief Reset count of consecutive player passes to 0.
     */
    void refreshPass();

    /**
     * @brief Add one to the count of consecutive passes.
     */
    void incrementPass();

    /**
     * @brief Check if player object is currently placing tiles.
     * @return true Player is currently placing tiles.
     * @return false Player is not currently placing tiles.
     */
    bool isPlacing() const;

    /**
     * @brief Set player status to currently placing tiles.
     */
    void startPlacing();

    /**
     * @brief Set player status to not currently placing tiles.
     */
    void donePlacing();

    /**
     * @brief Check what board axis the player currently allowed
     * to place tiles across.
     * @return Direction Enumeration value representing axis.
     */
    Direction getDirection() const;

    /**
     * @brief Set the board axis that the player is currently allowed
     * to place tiles across.
     */
    void setDirection(Direction);

    /**
     * @brief Return the board coordinate previously placed by the player
     * during the current turn, or an empty string if no previous tile.
     * @return std::string Board coordinate.
     */
    std::string prevTile() const;

    /**
     * @brief Record the latest tile placed by the player 
     * during the current turn. Automatically determines turn direction
     * once two tiles have been placed.
     */
    void updatePlace(const std::string&);

    /**
     * @brief Convert the player hand into the corresponding linked list string.
     * @return std::string Linked list string representing player hand.
     */
    std::string handToString() const;

    /**
     * @brief Prints the player hand as the corresponding linked list string.
     */
    void printHand() const;

    /**
     * @brief Verifies that all strings - name, hand, score - drawn from a core
     * save file are correctly formatted.
     * @return true Regex validation checks passed.
     * @return false Regex validation checks failed.
     */
    static bool validatePlayerStrings(const std::vector<std::string>&, 
        std::size_t);
};

#endif // AP_ASS2_PLAYER_H
