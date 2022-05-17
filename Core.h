#ifndef AP_ASS2_CORE_H
#define AP_ASS2_CORE_H

#include <regex>
#include <memory>
#include <random>
#include <chrono>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <utility>

#include "SaveState.h"
#include "LinkedList.h"
#include "Player.h"
#include "Board.h"

#define BINGO_BONUS 50

class Core {

    // Tracks the internal state of the core, influences progression.
    enum Control {
        QUIT,
        NEXT,
        SAME,
        INVALID
    };
    Control control;

    std::shared_ptr<LinkedList> bag;
    std::vector<Player> players;
    std::shared_ptr<Board> board;
    std::size_t current;

public:

    /**
     * @brief Construct a new core object with the given player names.
     * @param players The name of each player in the new game.
     */
    explicit Core(const std::vector<std::string>&);

    /**
    * @brief Construct a core object using previous game data.
    * @param save The save state object encapsulating desired previous game data.
    */
    explicit Core(SaveState&);

    ~Core() = default;

    /**
     * @brief Main function to initiate a new game with data stored in core fields.
     * Loops for each user action until a sequence of events which signals quit.
     */
    void runCore();

    /**
     * @brief Convert current internal core state to strings and save to file.
     * @param file File title where the core save state should be stored.
     */
    void saveCore(const std::string&);

    // Getters and setters used for converting into save state.
    std::shared_ptr<std::vector<Player>> getPlayers();
    std::shared_ptr<LinkedList> getBag();
    std::shared_ptr<Board> getBoard();
    std::size_t getCurrent() const;
    void printDuck();

private:

    /**
     * @brief For a new game, read and randomly shuffle the tile bag from file.
     * The pseudo-randomisation process is done using a seed derived from time.
     * @return std::unique_ptr<LinkedList> List pointer representing tile bag.
     */
    static std::unique_ptr<LinkedList> createBag();

    /**
     * @brief Read the user's desired action from standard input.
     * @param action Vector that user's decision should be read into.
     */
    static void getInput(std::vector<std::string>&);

    /**
    * @brief Move to the next player by updating internal core state.
    */
    void changeTurn();

    /**
     * @brief Print to standard all information required when transitioning 
     * between different player's turns. Includes player's name, 
     * score, hand, and board.
     */
    void displayTurn();

    /**
     * @brief Print all necessary information at the end or termination of a 
     * game. Includes scores for each player and determination of the overall 
     * winner.
     */
    void displayEnd();

    /**
     * @brief Ensure an action exists and update state after action is 
     * performed. If no tiles are left in the bag or either player hand, 
     * or a player exceeds their allocated pass limit, the game will terminate.
     * @param action The strings specifying action to be performed.
     */
    void doAction(const std::vector<std::string>&);

    /**
     * @brief Delegate processes based on type of user's specified action.
     * Core's internal flow control is automatically updated given certain
     * conditions: if the player has passed, move to the next player; if the
     * game has been saved remain on the same player, and quit if the player
     * has chosen to do so.
     * @param player Reference to the player object that has current turn.
     * @param action Processed strings representing the player's chosen action.
     */
    void handleAction(Player&, const std::vector<std::string>&);

    /**
     * @brief Validate input and select relevant placing process.
     * @param player Reference to the player object that has current turn.
     * @param action Processed strings representing the player's chosen action.
     */
    void handlePlace(Player&, const std::vector<std::string>&);

    /**
     * @brief Refill hand when player has placed tiles and finished their turn.
     * Core is signalled to transition to the next player in queue. Restrictions
     * on player tile placement imposed by Core::verifyPlace() are removed.
     * @param player Reference to the player object that has current turn.
     */
    void placeDone(Player&);

    /**
     * @brief Take specified tile in player's hand and place it on the 
     * active board. Find and update the current player's score if the tile 
     * placement was valid. Player's pass count is also reset, 
     * and bingo adds fifty to the score.
     * @param player Reference to the player object that has current turn.
     * @param action Processed strings representing the player's chosen action.
     */
    void placeTile(Player&, const std::vector<std::string>&);

    /**
     * @brief Place the tile specified in the user's action onto the active 
     * board. Derives the board coordinates and specified letter from action 
     * strings and return the value of the created tile to be added to 
     * player score.
     * @param action Processed strings representing the player's chosen action.
     * @return int Tile value of the letter added to the board.
     */
    int insertTile(const std::vector<std::string>&);

    /**
     * @brief Verifies that the player's specified tile placement is valid
     * within the context of their current turn. Consecutive tile placements
     * must be colinear, and if they are not adjacent all tiles on the linear
     * path between them should also be occupied.
     * @return Boolean signifying if the specified position is valid.
     */
    bool verifyPlace(Player&, const std::vector<std::string>&);

    /**
     * @brief Replace specified tile in player hand with random tile from bag.
     * Core is signalled to transition to the next player's turn afterward.
     * @param player Reference to the player object that has current turn.
     * @param action Processed strings representing the player's chosen action.
     */
    void replaceTile(Player&, const std::vector<std::string>&);
};

#endif // AP_ASS2_CORE_H
