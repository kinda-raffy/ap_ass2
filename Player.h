#ifndef AP_ASS2_PLAYER_H
#define AP_ASS2_PLAYER_H

#define HAND_SIZE 7

#include <regex>
#include <string>
#include <vector>

// Tracks the colinearity of players consecutive tile additions each turn.
enum Direction {
    X_AXIS,
    Y_AXIS,
    NONE
};

class LinkedList;

class Player {

    std::string name;
    std::shared_ptr<LinkedList> hand;
    int passes;
    int score;
    bool placing;

    Direction direction;
    std::vector<std::string> turn;

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

    // For validating consecutive tile additions.
    Direction getDirection() const;
    void setDirection(Direction);
    std::string prevTile() const;
    void updatePlace(const std::string&);

    std::string handToString() const;
    void printHand() const;

    static bool validatePlayerStrings(const std::vector<std::string>&, 
        std::size_t);
};


#endif //AP_ASS2_PLAYER_H
