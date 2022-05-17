#ifndef ASSIGN2_SAVE_STATE_H
#define ASSIGN2_SAVE_STATE_H

#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>

class Core;

class SaveState {

    // Stores string representations of all board state objects.
    std::string tiles;
    std::string board; 
    std::vector<std::string> players;
    std::vector<std::string> hands;
    std::vector<int> scores;
    std::size_t current;

public:

    /**
     * @brief Create a save state using saved core text file. Accepts the file
     * title as a path string and auto deduces player count and board size. 
     * Might have accidentally done an extension by allowing 
     * this to be variable size.
     */
    SaveState(const std::string&);

    /**
     * @brief Create a save state using a core object. Converts state of the 
     * core object into string layout and store in save state fields. Call
     * `SaveState::saveToFile()` to save core state strings as file.
     */
    SaveState(Core&);

    ~SaveState() = default;

    /**
     * @brief Write all save state strings to a `.save` file. String arg
     * is the path location and title of the file to be created or overwritten.
     */
    void saveToFile(const std::string&) const;

    // Getters used for creating a core object using a save state object.
    std::string& getTiles();
    std::string& getBoard();
    std::shared_ptr<std::vector<std::string>> getPlayers();    
    std::shared_ptr<std::vector<std::string>> getHands();
    std::shared_ptr<std::vector<int>> getScores();
    std::size_t getCurrent();

private:

    /**
     * @brief Reads all lines in the specified save file into supplied vector.
     * 
     */
    static void readSaveFile(const std::string&, std::vector<std::string>&);

    /**
     * @brief Verifies that strings correspond to save file layout.
     * @return true The string args pass regex validation checks.
     * @return false Regex validation checks failed.
     */
    static bool validateSaveString(const std::vector<std::string>&);
};

#endif // ASSIGN2_SAVE_STATE_H
