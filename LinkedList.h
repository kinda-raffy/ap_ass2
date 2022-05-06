#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <memory>
#include <iostream>
#include <string>
#include <sstream>

class LinkedList {

   std::shared_ptr<Node> head;
   std::shared_ptr<Node> tail;
   int length;

public:

   LinkedList();
   LinkedList(const std::string&);
   LinkedList(const LinkedList&);
   ~LinkedList() = default;

   char pop();
   bool remove(char);
   void append(char);
   void append(std::unique_ptr<Tile> tile);
   int size() const;

   std::string toString() const;
};

#endif // ASSIGN2_LINKEDLIST_H
