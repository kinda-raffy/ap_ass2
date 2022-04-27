#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"
#include <memory>

class Node {

   // Node object owns composed tile, but doesn't own next node.

   // Tile* tile;
   // Node* next;

   // TODO: Refactor to use smart pointers.

   std::unique_ptr<Tile> tile;
   // std::make_unique<Tile>(...);

   std::shared_ptr<Node> next;
   // std::make_shared<Node>(...);

public:

   Node(std::unique_ptr<Tile> Tile, std::shared_ptr<Node> Node);
   Node(const Node&);
   ~Node();

   // Getters and setters technically superfluous, but easier to parse.
   std::shared_ptr<Node> getNext();
   void setNext(std::shared_ptr<Node> next);

   std::unique_ptr<Tile> getTile();
   void setTile(std::unique_ptr<Tile> tile);

   char getLetter() const;
};

#endif // ASSIGN2_NODE_H
