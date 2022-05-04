#include "LinkedList.h"

LinkedList::LinkedList()
    : head {nullptr}, tail {nullptr}, length {0} {
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
        if (current == head) {
            head = head->getNext();
        } else {
            previous->setNext(current->getNext());
        }
        success = true;
        --length;
    }
    return success;
}

int LinkedList::size() const {
    return length;
}

void LinkedList::print() const {
    std::cout << "Your hand is " << std::endl;
    std::shared_ptr<Node> current = head;
    while (current != nullptr) {
        std::cout << current->getLetter() << '-' << current->getValue() << ',';
        current = current->getNext();
    }
}
