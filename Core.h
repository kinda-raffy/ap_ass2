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

    explicit Core(const std::vector<std::string>&);
    explicit Core(SaveState&);
    ~Core() = default;

    void runCore();
    void saveCore(const std::string&);

    std::shared_ptr<std::vector<Player>> getPlayers();
    std::shared_ptr<LinkedList> getBag();
    std::shared_ptr<Board> getBoard();
    std::size_t getCurrent() const;
    void printDuck();

private:

    static std::unique_ptr<LinkedList> createBag();
    static void getInput(std::vector<std::string>&);

    void changeTurn();
    void displayTurn();
    void displayEnd();

    // Action handling functions.
    void doAction(const std::vector<std::string>&);
    void handleAction(Player&, const std::vector<std::string>&);
    void handlePlace(Player&, const std::vector<std::string>&);
    void placeDone(Player&);
    void placeTile(Player&, const std::vector<std::string>&);
    int insertTile(const std::vector<std::string>&);
    void replaceTile(Player&, const std::vector<std::string>&);
};

#endif //AP_ASS2_CORE_H
