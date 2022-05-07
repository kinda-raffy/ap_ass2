#ifndef AP_ASS2_PLAYER_H
#define AP_ASS2_PLAYER_H

#include "LinkedList.h"

#define HAND_SIZE 7

using uniqPtr_LL = std::unique_ptr<LinkedList>;
using sharPtr_LL = std::shared_ptr<LinkedList>;

class Player {

    std::string name;
    sharPtr_LL hand;
    int consecutivePasses;
    int score;

    void setNewHand(sharPtr_LL tileBag);
    void setLoadedHand(int playerNum, std::string fileName);


public:
    Player(std::string name, sharPtr_LL tileBag,
           int score=-1, int playerNum=-1,
           std::string fileName="");
    ~Player();

    std::string getName() const;
    int getScore() const;
    void setScore(int);
    void addScore(int);
    sharPtr_LL getHand() const;

    int getPass() const;
    void refreshPass();
    void incrementPass();

    std::string handToString() const;
    void printHand() const;
};


#endif //AP_ASS2_PLAYER_H
