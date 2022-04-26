#include "LinkedList.h"

LinkedList::LinkedList() 
   : head {nullptr}, tail {nullptr}, length {0} {
}

LinkedList::LinkedList(const LinkedList &other)
   : head {nullptr}, tail {nullptr}, length {other.length} {
   // TODO: Delegate to base constructor and deep copy all source nodes.
}

LinkedList::~LinkedList() {
}

void LinkedList::append(char letter) {
   append(new Tile {letter});
}

void LinkedList::append(Tile *tile) {
   Node *node {new Node {tile, nullptr}};
   if (head == nullptr) {
      head = tail = node;
   } else {
      tail->next = node;
      tail = tail->next;
   }
   ++length;
}

bool LinkedList::remove(Tile* tile) {
   remove(tile->letter);
}

bool LinkedList::remove(char letter) {
   bool success {false};
   Node *current {head}, *previous {nullptr};
   while (current != nullptr && current->tile->letter != letter) {
      previous = current;
      current = current->next;
   }
   if (current != nullptr) {
      if (current == head) {
         head = head->next;
      } else {
         previous->next = current->next;
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