#include <fstream>
#include "Player.h"

Player::Player(std::string name, sharPtr_LL tileBag,
               int score, int playerNum, std::string fileName) {
    this->name = name;
    if (fileName.empty()) {
        // New game.
        this->score = 0;
        setNewHand(tileBag);
    } else {
        // Load game.
        this->score = score;
        setLoadedHand(playerNum, fileName);
    }
}


Player::~Player() = default;


void Player::setNewHand(sharPtr_LL tileBag) {
    // Set a new hand.
    const int _handSize {7};
    uniqPtr_LL newHand = std::make_unique<LinkedList>();
    for (int i = 0; i < _handSize; i++)
        newHand->append(tileBag->pop());
    this->hand = std::move(newHand);
}

void Player::setLoadedHand(int playerNum, std::string fileName) {
    // Load hand from file.
    std::ifstream file;
    if (!file.is_open()) {
        throw std::runtime_error("Could not find file: " + fileName);
    }
    uniqPtr_LL loadedHand = std::make_unique<LinkedList>();
    // Iterate to line number where saved hand is located.
    const int _lineNum {3 * playerNum};
    std::string line;
    for (int i = 0; i < _lineNum; ++i)
        std::getline(file, line);
    // TODO - Perform string splitting to get letters.
    this->hand = std::move(loadedHand);
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

std::string Player::handToString() const {
    // FIXME - Fix LL print.
    return "";
}

void Player::printHand() const {
    std::cout << "Your hand is" << std::endl;
    std::cout << handToString() << std::endl;
}
