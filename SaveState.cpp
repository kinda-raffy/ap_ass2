#include "SaveState.h"

SaveState::SaveState(const std::string &save)
    : save {save}, partition {save.find(' ')} {
}

SaveState::SaveState(const SaveState &saveState)
    : save {saveState.save}, partition {saveState.partition} {
}

size_t SaveState::getSize() const {
    std::size_t size {0};
    if (partition != std::string::npos) {
        size = std::stoi(save.substr(0, partition));
    }
    return size;
}

std::string SaveState::getLetters() const {
    return save.substr(partition + 1);
}
