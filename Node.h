#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node {

   // Node object owns composed tile, but doesn't own next node.
   Tile* tile;
   Node* next;

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
