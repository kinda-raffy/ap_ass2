#ifndef AP_ASS2_TILEBAG_H
#define AP_ASS2_TILEBAG_H

#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <chrono>
#include "LinkedList.h"

using uniqPtr_LL = std::unique_ptr<LinkedList>;

uniqPtr_LL createNewBag();
uniqPtr_LL loadSavedBag(const std::string& fileName);
std::string tileBagToString(uniqPtr_LL& tileBag);

#endif //AP_ASS2_TILEBAG_H
