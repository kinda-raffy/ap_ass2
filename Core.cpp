#include "Core.h"
#include "TileBag.cpp"

void Core::printDuck() {
    std::cout << "https://imgur.com/gallery/w9Mjo4y" << std::endl;
}

Core::Core(const std::vector<std::string> playerNames,
           const uniqPtr_LL _board, const uniqPtr_LL _bag,
           int playerTurn) : current {playerTurn} {
    if (current == -1) {
        // New game.
        this->bag = std::move(createNewBag());
        this->players = createPlayers(playerNames);
        this->board = std::make_unique<Board>(Board());
        this->current = 1;

    } else {
        // Load game.
        this->bag = std::move(_bag);
        this->players = (playerNames);
        this->board = std::move(_board);
        this->current = playerTurn;
    }
}

Core::Core(const SaveState&) {

}

std::vector<Player> Core::createPlayers(const std::vector<std::string> playerNames) {
    // Check if bag is nullptr.
    if (bag == nullptr) { throw std::runtime_error("Bag is nullptr."); }
    //
    const std::size_t _numPlayers = playerNames.size();
    std::vector<Player> _players;
    _players.reserve(_numPlayers);
    for (int i {0}; i < _numPlayers; i++) {
        _players.emplace_back(Player(playerNames[i], bag));
    }
    return _players;
}

