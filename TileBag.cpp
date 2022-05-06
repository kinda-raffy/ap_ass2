#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include "LinkedList.h"

using uniqPtr_LL = std::unique_ptr<LinkedList>;


 uniqPtr_LL createNewBag() {
    std::ifstream file;
    file.open("ScrabbleTiles.txt");
    if(!file.is_open()) {
        throw std::runtime_error("Could not open tile bag file");
    }
    // Temporary vector to shuffle letters.
    std::unique_ptr<std::vector<char>> charList = std::make_unique<std::vector<char>>();
    charList->reserve(98);
    // Populate charList with letters from file.
    std::string line;
    while(std::getline(file, line)) { charList->push_back(line[0]); }
    file.close();
    // Shuffle charList.
    auto eng = std::default_random_engine{};
    std::shuffle(charList->begin(), charList->end(), eng);
    // Add to tile bag.
    uniqPtr_LL tileBag = std::make_unique<LinkedList>();
    for (auto& letter : *charList) { tileBag->append(letter); }
    return std::move(tileBag);
}

uniqPtr_LL loadSavedBag(const std::string& fileName) {
    std::ifstream file;
    if (!file.is_open()) {
        throw std::runtime_error("Could not find file: " + fileName);
    }
    uniqPtr_LL tileBag = std::make_unique<LinkedList>();
    // Iterate to line number where saved bag is located.
    const int _lineNum {8};
    std::string line;
    for (int i = 0; i < _lineNum; ++i)
        std::getline(file, line);
    // TODO - Perform string splitting to get letters.
 }

 std::string tileBagToString(uniqPtr_LL& tileBag) {
     std::string bagString;
     const int _bagSize {tileBag->size()};
     for (int i = 0; i < _bagSize; ++i) {}  // TODO - Implement.
 }

