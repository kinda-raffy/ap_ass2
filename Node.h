#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"
#include <memory>

class Node {

   // Tile* tile;
   // Node* next;

   // Node object owns tile, but doesn't own next node.
   std::unique_ptr<Tile> tile;
   std::shared_ptr<Node> next;

public:

   Node(char);
   Node(std::unique_ptr<Tile>);
   Node(std::unique_ptr<Tile>, std::shared_ptr<Node>);
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
