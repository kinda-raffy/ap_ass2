#include "LinkedList.h"

LinkedList::LinkedList()
    : head {nullptr}, tail {nullptr}, length {0} {
}

LinkedList::LinkedList(const std::string &list)
    : LinkedList {} {
    // Construct a linked list object using its string representation.
    std::istringstream inputString {list};
    std::string node;
    // Append each letter to list after erasing any leading whitespace.
    while (std::getline(inputString, node, ',')) {
        node.erase(0, node.find_first_not_of(' '));
        // Only leading character required since tile values stored internally.
        append(node.at(0));
    }
}

LinkedList::LinkedList(const LinkedList &source)
    : head {nullptr}, tail {nullptr}, length {source.length} {
    std::size_t index {0};
    // Initialise pointers used for iterating over the list.
    std::shared_ptr<Node> current {source.head}, previous {nullptr};
    while (index < length) {
        // Construct a copy of current node in source list.
        std::shared_ptr<Node> node {std::make_shared<Node>(*current)};
        tail = node;
        // Append copied node to the end of the list.
        if (head == nullptr) {
            previous = head = node;
        } else {
            previous->setNext(node);
            previous = previous->getNext();
        }
        // Move pointer to next node in list being copied.
        current = current->getNext();
    }
}

void LinkedList::append(char letter) {
    // Create a new tile using the char arg and delegate.
    std::unique_ptr<Tile> tile {std::make_unique<Tile>(letter)};
    append(std::move(tile));
}

void LinkedList::append(std::unique_ptr<Tile> tile) {
    // Create a new node using tile arg and append.
    std::shared_ptr<Node> node {std::make_shared<Node>(std::move(tile))};
    if (head == nullptr) {
        head = tail = node;
    } else {
        tail->setNext(node);
        tail = tail->getNext();
    }
    ++length;
}

bool LinkedList::contains(char letter) const {
    // Iterate over the list nodes until the character is found or end reached.
    std::shared_ptr<Node> current{head};
    bool found {false};
    while (current != nullptr && !found) {
        if (current->getLetter() == letter) {
            found = true;
        }
        current = current->getNext();
    }
    // Return true if character was found or false if not.
    return found;
}

bool LinkedList::replace(char letter, char replace) {
    bool success {false};
    // Iterate over list to find first occurance of letter.
    std::shared_ptr<Node> current {head};
    while (current != nullptr && !success) {
        // If letter is encountered, replace with replacement character.
        if (current->getLetter() == letter) {
            current->setLetter(replace);
            success = true;
        }
        // Move to next node in the list.
        current = current->getNext();
    }
    return success;
}

char LinkedList::pop() {
    // Delete the first node and return the contained character.
    char result {'\0'};
    if (head != nullptr) {
        result = head->getLetter();
        head = head->getNext();
        --length;
    }
    // Returns the first character or null if the list is empty.
    return result;
}

bool LinkedList::remove(char letter) {
    bool success {false};
    // Iterate over the list to find the first occurance of the letter.
    std::shared_ptr<Node> current {head}, previous {nullptr};
    while (current != nullptr && current->getLetter() != letter) {
        previous = current;
        current = current->getNext();
    }
    if (current != nullptr) {
        // If the character was found, undertake relevant deletion process.
        if (length == 1) {
            head = tail = nullptr;
        } else if (current == head) {
            head = head->getNext();
        } else if (current == tail) {
            tail = previous;
        } else {
            previous->setNext(current->getNext());
        }
        // Decrease length and indicate successful deletion.
        success = true;
        --length;
    }
    return success;
}

std::size_t LinkedList::size() const {
    return length;
}

std::string LinkedList::toString() const {
    std::stringstream stream {};
    std::shared_ptr<Node> current {head};
    // Iterate over each node and convert into corresponding string fragment.
    while (current != nullptr) {
        stream << current->getLetter() << '-' << current->getValue();
        // Don't add comma to the tail node fragment.
        if (current != tail) {
            stream << ", ";
        }
        // Move pointer to next node.
        current = current->getNext();
    }
    // Convert string stream into an std::string and return.
    return stream.str();
}

bool LinkedList::validateListString(const std::string &list) {
    // Check that the string is either empty or in the correct format.
    const std::regex pattern {"([A-Z]{1}-[0-9]{1,2}(, )?)*"};
    return std::regex_match(list, pattern);
}
