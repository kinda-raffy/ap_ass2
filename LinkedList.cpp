#include "LinkedList.h"

LinkedList::LinkedList()
    : head {nullptr}, tail {nullptr}, length {0} {
}

LinkedList::LinkedList(const LinkedList &source)
    : head {nullptr}, tail {nullptr}, length {source.length} {
    int index {0};
    // Node *current {source.head}, *previous {nullptr};
    std::shared_ptr <Node> current {source.head}, previous {source.head};
    while (index < length) {
        // Construct a copy of current node in source list.
        std::shared_ptr <Node> node{std::make_shared<Node>(*current)};
        tail = node;
        if (head == nullptr) {
            previous = head = node;
        } else {
            previous->setNext(node);
            previous = previous->getNext();
        }
        current = current->getNext();
    }
}

LinkedList::~LinkedList() {
    std::shared_ptr<Node> current{head}, next{nullptr};
    // Iterate over and delete all nodes in list.
    while (current != nullptr) {
        next = current->getNext();
        // delete current;
        current = next;
    }
}

// Create a new tile using the char arg and delegate.
void LinkedList::append(char letter) {
    append(std::make_shared<Tile>(letter));
}

// Create a new node using tile arg and append.
void LinkedList::append(std::shared_ptr<Tile> tile) {
    std::shared_ptr<Node> node {std::make_shared<Node>(*tile)};
    if (head == nullptr) {
        head = tail = node;
    } else {
        tail->setNext(node);
        tail = tail->getNext();
    }
    ++length;
}

bool LinkedList::remove(std::shared_ptr <Tile> tile) {
    remove(tile->getLetter());
}

bool LinkedList::remove(char letter) {
    bool success {false};
    std::shared_ptr<Node> current {head}, previous {};
    while (current != nullptr && current->getLetter() != letter) {
        previous = current;
        current->setNext(current->getNext());
    }
    if (current != nullptr) {
        if (current == head) {
            head->setNext(head->getNext());
        } else {
            previous->setNext(current->getNext());
        }
        // Free superfluous storage.
        // delete current;
        success = true;
        --length;
    }
    return success;
}

int LinkedList::size() const {
    return length;
}

void LinkedList::print() const {
    std::cout << "Your hand is\n";
   Node *current {head};
   while (current != nullptr) {
      std::cout << current->getTile()->getLetter() << '-' << current->getTile()->getValue() << ",";
      current = current->getNext();
   } std::cout << std::endl;
}