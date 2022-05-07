#include <fstream>
#include "Player.h"

Player::Player(std::string name, sharPtr_LL tileBag, int score, int playerNum,
               std::string fileName) : consecutivePasses {0} {
    this->name = name;
    if (fileName.empty()) {
        // New player.
        this->score = 0;
        setNewHand(tileBag);
    } else {
        // Load player.
        this->score = score;
        setLoadedHand(playerNum, fileName);
    }
}


Player::~Player() = default;


void Player::setNewHand(sharPtr_LL tileBag) {
    // Set a new hand.
    sharPtr_LL newHand = std::make_shared<LinkedList>();
    for (int i = 0; i < HAND_SIZE; i++)
        newHand->append(tileBag->pop());
    this->hand = newHand;
}

void Player::setLoadedHand(int playerNum, std::string fileName) {
    // Load hand from file.
    std::ifstream file;
    if (!file.is_open()) {
        throw std::runtime_error("Could not find file: " + fileName);
    }
    sharPtr_LL loadedHand = std::make_shared<LinkedList>();
    // Iterate to line number where saved hand is located.
    const int _lineNum {3 * playerNum};
    std::string line;
    for (int i = 0; i < _lineNum; ++i)
        std::getline(file, line);
    // TODO - Perform string splitting to get letters.
    this->hand = loadedHand;
}

std::string Player::getName() const {
    return this->name;
}

int Player::getScore() const {
    return this->score;
}

void Player::setScore(int score_) {
    this->score = score_;
}

void Player::addScore(int score_) {
    this->score += score_;
}

sharPtr_LL Player::getHand() const {
    return this->hand;
}

std::string Player::handToString() const {
    return hand->toString();
}

void Player::printHand() const {
    std::cout << "Your hand is" << std::endl;
    std::cout << handToString() << std::endl;
}

int Player::getPass() const {
    return this->consecutivePasses;
}

void Player::refreshPass() {
    this->consecutivePasses = 0;
}

void Player::incrementPass() {
    this->consecutivePasses++;
}
