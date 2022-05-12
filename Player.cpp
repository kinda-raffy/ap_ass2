#include <fstream>
#include <utility>
#include "Player.h"

Player::Player(const std::string &name, const std::string &hand, int score)
    : name {name}, hand {std::make_shared<LinkedList>(hand)}, 
      passes {0}, score {score}, placing {false} {
}

Player::Player(const std::string &name, const std::shared_ptr<LinkedList> bag)
    : name {name}, hand {std::make_shared<LinkedList>()}, 
      passes {0}, score {0}, placing {false} {
    // Transfer the requisite tiles to the player hand.
    for (std::size_t index {0}; index < HAND_SIZE; ++index) {
        hand->append(bag->pop());
    }
}

Player::~Player() = default;

std::string Player::getName() const {
    return this->name;
}

int Player::getScore() const {
    return this->score;
}

void Player::setScore(int score) {
    this->score = score;
}

void Player::addScore(int score) {
    this->score += score;
}

std::shared_ptr<LinkedList> Player::getHand() const {
    return this->hand;
}

std::string Player::handToString() const {
    return hand->toString();
}

void Player::printHand() const {
    std::cout << "Your hand is\n" << handToString() << std::endl;
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
    return placing;
}

void Player::startPlacing() {
    placing = true;
}

void Player::donePlacing() {
    placing = false;
}
