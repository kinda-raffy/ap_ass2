#include "LinkedList.h"
#include "Player.h"

#ifndef AP_ASS2_CORE_H
#define AP_ASS2_CORE_H

using uniqPtr_LL = std::unique_ptr<LinkedList>;
using sharPtr_LL = std::shared_ptr<LinkedList>;

class Core {
    /* 
        Harry Proposed Layout
        ~
        std::vector<Player> players;
        std::shared_ptr<LinkedList> tiles;
        std::unique_ptr<Board> board;
        int current; // Current player turn.
    */

    int numPlayers;
    int playerTurn;
    std::map<int, Player> players;
    sharPtr_LL tileBag;

    void runGame(std::map<int, Player> players,
            uniqPtr_LL boardState=nullptr,
            uniqPtr_LL tileBag=nullptr, int playerTurn=-1);

public:
    Core(int numPlayers);
    ~Core();

    void newGame();
    void loadGame();
    void saveGame();

    void printDuck();
};


#endif //AP_ASS2_CORE_H
