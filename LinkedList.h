#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {

   Node* head;
   Node* tail;
   int length;

public:

   LinkedList();
   LinkedList(const LinkedList&);
   ~LinkedList();

   void append(char);
   void append(Tile*);
   bool remove(char);
   bool remove(Tile*);
   int size() const;

   void print() const;
};

#endif // ASSIGN2_LINKEDLIST_H
