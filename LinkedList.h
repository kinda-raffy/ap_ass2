#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <memory>

class LinkedList {

   Node* head;
   Node* tail;
   int length;

   // std::shared_ptr<Node> head;
   // std::shared_ptr<Node> tail;

public:

   LinkedList();
   LinkedList(const LinkedList&);
   ~LinkedList();

   void append(char);
   void append(Tile*);
   bool remove(char);
   bool remove(Tile*);
   int size() const;
};

#endif // ASSIGN2_LINKEDLIST_H
