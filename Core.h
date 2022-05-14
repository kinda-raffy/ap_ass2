#ifndef AP_ASS2_CORE_H
#define AP_ASS2_CORE_H

// #include <functional>
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

// Core iteration control constants.
#define QUIT 0
#define NEXT_PLAYER 1
#define SAME_PLAYER 2
#define INVALID_ACT 3

// Rule constants.
#define BINGO_BONUS 50

class Core {

    std::shared_ptr<LinkedList> bag;
    std::vector<Player> players;
    std::shared_ptr<Board> board;
    std::size_t current;
    /*
        Maintain a pointer to the requisite handling function.
        std::function<int(Player &player, const std::vector<std::string> &action)> handler;
    */

public:

    explicit Core(const std::vector<std::string>&);
    explicit Core(SaveState&);
    ~Core() = default;

    void runCore();
    void saveCore(const std::string&);

    // friend std::ostream& operator<<(std::ostream& os, const Core& core);

    std::shared_ptr<std::vector<Player>> getPlayers();
    std::shared_ptr<LinkedList> getBag();
    std::shared_ptr<Board> getBoard();
    std::size_t getCurrent() const;
    void printDuck();

private:

    static std::unique_ptr<LinkedList> createBag();

    void changeTurn();
    void displayTurn();
    void displayEnd();

    // Action handling functions.
    int handleAction(const std::vector<std::string>&);
    int handlePlace(Player&, const std::vector<std::string>&);
    int placeDone(Player&);
    int placeTile(Player&, const std::vector<std::string>&);
    int replaceTile(Player&, const std::vector<std::string>&);
};

#endif //AP_ASS2_CORE_H
