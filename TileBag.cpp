#include "TileBag.h"

 uniqPtr_LL createNewBag() {
    std::ifstream file;
    file.open("ScrabbleTiles.txt");
    if(!file.is_open()) {
        throw std::runtime_error("Could not open tile bag file");
    }
    // Temporary vector to shuffle letters.
    std::vector<char> charList(98);
    // Populate charList with letters from file.
    std::string line;
    while(std::getline(file, line)) { charList.push_back(line[0]); }
    file.close();
    // Shuffle charList.
    auto eng = std::default_random_engine{};
    std::shuffle(charList.begin(), charList.end(), eng);
    // Add to tile bag.
    uniqPtr_LL tileBag = std::make_unique<LinkedList>();
    for (auto& letter : charList) { tileBag->append(letter); }
    return tileBag;
}
