#include <iostream>
#include "LinkedList.h"

LinkedList::LinkedList() 
   : head {nullptr}, tail {nullptr}, length {0} {
}

LinkedList::LinkedList(const LinkedList &source)
   : head {nullptr}, tail {nullptr}, length {source.length} {
   // TODO: Delegate to base constructor and deep copy all source nodes.
   int index {0};
   Node *current {source.head}, *previous {nullptr};
   while (index < length) {
      // Construct a copy of current node in source list.
      Node* node {new Node {*current}};
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
   Node *current {head}, *next {nullptr};
   // Iterate over and delete all nodes in list.
   while (current != nullptr) {
      next = current->getNext();
      delete current;
      current = next;
   }
}

void LinkedList::append(char letter) {
   append(new Tile {letter});
}

void LinkedList::append(Tile *tile) {
   Node *node {new Node {tile, nullptr}};
   if (head == nullptr) {
      head = tail = node;
   } else {
      tail->setNext(node);
      tail = tail->getNext();
   }
   ++length;
}

bool LinkedList::remove(Tile* tile) {
   remove(tile->getLetter());
}

bool LinkedList::remove(char letter) {
   bool success {false};
   Node *current {head}, *previous {nullptr};
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
      delete current;
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