#ifndef AP_ASS2_PLAYER_H
#define AP_ASS2_PLAYER_H

#include "LinkedList.h"

#define HAND_SIZE 7

class Player {

    std::string name;
    std::shared_ptr<LinkedList> hand;
    int passes;
    int score;
    bool placing;

public:

    Player(const std::string&, std::shared_ptr<LinkedList>);
    Player(const std::string&, const std::string&, int);
    ~Player();

    std::string getName() const;
    int getScore() const;
    void setScore(int);
    void addScore(int);
    std::shared_ptr<LinkedList> getHand() const;

    int getPass() const;
    void refreshPass();
    void incrementPass();

    bool isPlacing() const;
    void startPlacing();
    void donePlacing();

    std::string handToString() const;
    void printHand() const;

    static bool validatePlayerStrings(const std::vector<std::string>&, 
        std::size_t);
};


#endif //AP_ASS2_PLAYER_H
