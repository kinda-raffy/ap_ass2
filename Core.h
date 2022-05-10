#ifndef AP_ASS2_CORE_H
#define AP_ASS2_CORE_H

#include <vector>
#include <sstream>
#include "SaveState.h"
#include "LinkedList.h"
#include "Player.h"
#include "Board.h"
#include "TileBag.h"

using uniqPtr_LL = std::unique_ptr<LinkedList>;
using sharPtr_LL = std::shared_ptr<LinkedList>;

// Core iteration control constants.
#define QUIT 0
#define NEXT_PLAYER 1
#define SAME_PLAYER 2
#define INVALID_ACT 3

// Game rule constants.
#define BINGO_BONUS 50

class Core {

    std::vector<Player> players;
    std::shared_ptr<LinkedList> bag;
    std::shared_ptr<Board> board;
    int current;

    std::vector<Player> createPlayers(std::vector<std::string>);
    int handleAction(std::vector<std::string>);
    void changeTurn();
    void displayTurn();
    void displayEnd();

public:

    explicit Core(std::vector<std::string>);
    explicit Core(const SaveState&);
    ~Core() = default;

    void runGame();
    void saveGame(std::string);

    friend std::ostream& operator << (std::ostream& os, const Core& core);
    void printDuck();

    std::shared_ptr<std::vector<Player>> getPlayers();
    std::shared_ptr<LinkedList> getBag();
    std::shared_ptr<Board> getBoard();
    int getCurrent() const;
};


#endif //AP_ASS2_CORE_H
