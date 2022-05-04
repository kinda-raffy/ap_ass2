#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <memory>
#include <iostream>

class LinkedList {

   int length;
   std::shared_ptr<Node> head;
   std::shared_ptr<Node> tail;

public:

   LinkedList();
   LinkedList(const LinkedList&);
   ~LinkedList();

   char pop();
   bool remove(char);
   void append(char);
   void append(std::unique_ptr<Tile> tile);
   int size() const;

   void print() const;
};

#endif // ASSIGN2_LINKEDLIST_H
