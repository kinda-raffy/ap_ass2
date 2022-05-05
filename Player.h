#include "LinkedList.h"

#ifndef AP_ASS2_PLAYER_H
#define AP_ASS2_PLAYER_H

using uniqPtr_LL = std::unique_ptr<LinkedList>;
using sharPtr_LL = std::shared_ptr<LinkedList>;

class Player {

    std::string name;
    int score;
    uniqPtr_LL hand;

    void setNewHand(sharPtr_LL tileBag);
    void setLoadedHand(int playerNum, std::string fileName);


public:
    Player(std::string name, sharPtr_LL tileBag,
           int score=-1, int playerNum=-1,
           std::string fileName="");
    ~Player();

    std::string getName();
    int getScore();
    void setScore(int);

    std::string handToString();
    void printHand();
};


#endif //AP_ASS2_PLAYER_H
