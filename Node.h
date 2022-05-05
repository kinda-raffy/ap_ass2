#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"
#include <memory>

class Node {

   // Node object owns tile, but doesn't own next node.
   std::unique_ptr<Tile> tile;
   std::shared_ptr<Node> next;

public:

   Node(char);
   Node(std::unique_ptr<Tile>);
   Node(std::unique_ptr<Tile>, std::shared_ptr<Node>);
   Node(const Node&);
   ~Node() = default;

   std::shared_ptr<Node> getNext();
   void setNext(std::shared_ptr<Node> next);

   // Access and alter tile through node object.
   int getValue() const;
   char getLetter() const;
   void setLetter(char);
};

#endif // ASSIGN2_NODE_H
