#ifndef AP_ASS2_CORE_H
#define AP_ASS2_CORE_H

#include <vector>
#include "LinkedList.h"
#include "Player.h"
#include "Board.h"

using uniqPtr_LL = std::unique_ptr<LinkedList>;
using sharPtr_LL = std::shared_ptr<LinkedList>;

// Forward declaration could fix yesterday's error.
class SaveState;

class Core {

    std::vector<Player> players;
    std::shared_ptr<LinkedList> bag;
    std::unique_ptr<Board> board;
    int current;

public:

    Core();
    Core(const SaveState&);

    // Can you set unique pointers to null? I've also fixed syntax here.
    Core(std::vector<std::string> playerNames, uniqPtr_LL _board = nullptr,
        uniqPtr_LL _bag = nullptr, int playerTurn = -1);
    ~Core();

    void runGame();
    void saveGame();

    void printDuck();

    std::vector<Player> createPlayers(
        const std::vector<std::string> playerNames);

private:

    // I've put this here to separate visually from the fields area.
    std::vector<Player> createPlayers(int);
};


#endif //AP_ASS2_CORE_H
