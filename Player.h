#ifndef AP_ASS2_PLAYER_H
#define AP_ASS2_PLAYER_H

#include "LinkedList.h"

#define HAND_SIZE 7

using uniqPtr_LL = std::unique_ptr<LinkedList>;
using sharPtr_LL = std::shared_ptr<LinkedList>;

class Player {

    std::string name;
    sharPtr_LL hand;
    int passes;
    int score;

    void setNewHand(const sharPtr_LL& tileBag);
    void setLoadedHand(int playerNum, const std::string& fileName);


public:

    Player(const std::string&, const std::string&, int);
    Player(std::string name, const sharPtr_LL& tileBag,
           int score=-1, int playerNum=-1,
           const std::string& fileName="");
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
