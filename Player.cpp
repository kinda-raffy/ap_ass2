#include <fstream>
#include <utility>

#include "LinkedList.h"
#include "Player.h"

Player::Player(const std::string &name, const std::string &hand, int score)
    : name {name}, hand {std::make_shared<LinkedList>(hand)}, passes {0}, 
      score {score}, placing {false}, direction {Direction::NONE} {
}

Player::Player(const std::string &name, const std::shared_ptr<LinkedList> bag)
    : name {name}, hand {std::make_shared<LinkedList>()}, 
      passes {0}, score {0}, placing {false}, direction {Direction::NONE} {
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
    turn.clear();
    direction = Direction::NONE;
}

Direction Player::getDirection() const {
    return direction;
}

std::string Player::prevTile() const {
    std::size_t length {turn.size()};
    return (length == 0) ? "" : turn.at(length - 1);
}

void Player::updatePlace(const std::string &coordinate) {
    try {
        if (!std::regex_match(coordinate, std::regex("[A-Z]{1}[0-9]{1,2}"))) {
            throw std::runtime_error("Invalid board coordinate.");
        }
        turn.push_back(coordinate);
        if (turn.size() == 2) {
            std::string previous {prevTile()};
            if (previous.at(0) == coordinate.at(0)) {
                direction = Direction::X_AXIS;
            } else if (previous.substr(1) == coordinate.substr(1)) {
                direction = Direction::Y_AXIS;
            } else {
                throw std::runtime_error("Player cannot place tile here.");
            }
        }
    } catch (const std::runtime_error &re) {
        std::cout << re.what() << std::endl;
    }
}

bool Player::validatePlayerStrings(const std::vector<std::string> &lines, 
    std::size_t start) {

    bool correct {true};
    // Ensure player's name is all uppercase alpha characters.
    correct = correct 
        && std::regex_match(lines.at(start++), std::regex("[A-Z]+"));
    // Ensure player's score is numeric.
    correct = correct 
        && std::regex_match(lines.at(start++), std::regex("[0-9]+"));
    // Ensure hand is in the correct linked list string layout.
    correct = correct && LinkedList::validateListString(lines.at(start));
    return correct;
}