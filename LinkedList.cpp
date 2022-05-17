#include "LinkedList.h"

LinkedList::LinkedList()
    : head {nullptr}, tail {nullptr}, length {0} {
}

// Construct a linked list object using its string representation.
LinkedList::LinkedList(const std::string &list)
    : LinkedList {} {
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
    int index {0};
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
        current = current->getNext();
    }
}

// Create a new tile using the char arg and delegate.
void LinkedList::append(char letter) {
    std::unique_ptr<Tile> tile {std::make_unique<Tile>(letter)};
    append(std::move(tile));
}

// Create a new node using tile arg and append.
void LinkedList::append(std::unique_ptr<Tile> tile) {
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
    std::shared_ptr<Node> current{head};
    bool found {false};
    while (current != nullptr) {
        if (current->getLetter() == letter) {
            found = true;
        }
        current = current->getNext();
    }
    return found;
}

// Replaces the first instance of first letter with second.
bool LinkedList::replace(char letter, char replace) {
    bool success {false};
    std::shared_ptr<Node> current {head};
    while (current != nullptr && !success) {
        if (current->getLetter() == letter) {
            current->setLetter(replace);
            success = true;
        } current = current->getNext();
    } 
    return success;
}

// Delete the first node and return the contained character.
char LinkedList::pop() {
    char result {'\0'};
    if (head != nullptr) {
        result = head->getLetter();
        head = head->getNext();
        --length;
    }
    return result;
}

bool LinkedList::remove(char letter) {
    bool success {false};
    std::shared_ptr<Node> current {head}, previous {nullptr};
    while (current != nullptr && current->getLetter() != letter) {
        previous = current;
        current = current->getNext();
    }
    if (current != nullptr) {
        // Superfluous storage auto deleted by smart pointers.
        if (length == 1) {
            head = tail = nullptr;
        } else if (current == head) {
            head = head->getNext();
        } else if (current == tail) {
            tail = previous;
        } else {
            previous->setNext(current->getNext());
        }
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
    while (current != nullptr) {
        stream << current->getLetter() << '-' << current->getValue();
        if (current != tail) {
            stream << ", ";
        }
        current = current->getNext();
    }
    return stream.str();
}

bool LinkedList::validateListString(const std::string &list) {
    const std::regex pattern {"([A-Z]{1}-[0-9]{1,2}(, )?)+"};
    return std::regex_match(list, pattern);
}
