#include <fstream>
#include <utility>
#include "Player.h"

Player::Player(std::string name, const sharPtr_LL& tileBag, int score, int playerNum,
               const std::string& fileName) : consecutivePasses {0} {
    this->name = std::move(name);
    // New player.
    this->score = 0;
    setNewHand(tileBag);
}


Player::~Player() = default;


void Player::setNewHand(const sharPtr_LL& tileBag) {
    // Set a new hand.
    sharPtr_LL newHand = std::make_shared<LinkedList>();
    for (int i = 0; i < HAND_SIZE; i++)
        newHand->append(tileBag->pop());
    this->hand = newHand;
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
