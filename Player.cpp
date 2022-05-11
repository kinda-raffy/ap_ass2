#include <fstream>
#include <utility>
#include "Player.h"

Player::Player(const std::string &name, const std::string &hand, int score)
        : name{name}, hand{std::make_shared<LinkedList>(hand)},
          passes{0}, score{score}, currentlyPlacing{false} {
}

Player::Player(std::string name, const std::shared_ptr<LinkedList> &tileBag,
               int score, int playerNum, const std::string &fileName)
        : passes{0}, currentlyPlacing{false} {
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
    return this->passes;
}

void Player::refreshPass() {
    this->passes = 0;
}

void Player::incrementPass() {
    this->passes++;
}

bool Player::isPlacing() const {
    return currentlyPlacing;
}

void Player::startPlacing() {
    currentlyPlacing = true;
}

void Player::donePlacing() {
    currentlyPlacing = false;
}
