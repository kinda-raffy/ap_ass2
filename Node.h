#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"
#include <memory>

class Node {

   // Node object owns composed tile, but doesn't own next node.
   Tile* tile;
   Node* next;

   // TODO: Refactor to use smart pointers.

   // std::unique_ptr<Tile> tile;
   // std::make_unique<Tile>(...);

   // std::shared_ptr<Node> next;
   // std::make_shared<Node>(...);

public:

   Node(Tile*, Node*);
   Node(const Node&);
   ~Node();

   // Getters and setters technically superfluous, but easier to parse.
   Node* getNext();
   void setNext(Node*);

   Tile* getTile();
   void setTile(Tile*);

   char getLetter() const;
};

#endif // ASSIGN2_NODE_H
