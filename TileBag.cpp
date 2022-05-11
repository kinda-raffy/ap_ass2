#include "TileBag.h"

uniqPtr_LL createNewBag() {
    std::ifstream file;
    file.open("ScrabbleTiles.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Could not open tile bag file");
    }

    // Temporary vector to shuffle letters.
    std::vector<char> charList;
    charList.reserve(98);

    // Populate charList with letters from file.
    std::string line;
    while (std::getline(file, line)) { charList.push_back(line.at(0)); }
    file.close();

    // Shuffle charList.
    std::default_random_engine randomEngine (
            std::chrono::system_clock::now().time_since_epoch().count());
    std::shuffle(charList.begin(), charList.end(), randomEngine);

    // Add to tile bag.
    uniqPtr_LL tileBag = std::make_unique<LinkedList>();
    for (auto &letter: charList) { tileBag->append(letter); }
    return tileBag;
}
