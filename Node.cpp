#include "Node.h"

Node::Node(Tile *tile, Node *next) 
   : tile {tile}, next {next} {
}

Node::Node(const Node &source)
   : tile {new Tile {source.getLetter()}}, next {nullptr} {
   // TODO: Should next be deep copied as well?
}

Node::~Node() {
   // Node object has ownership of tile, but not of next node.
   delete tile;
}

Node* Node::getNext() {
   return next;
}

void Node::setNext(Node *next) {
   // Nodes do not own the next node pointed to; do not delete next.
   this->next = next;
}

Tile* Node::getTile() {
   return tile;
}

void Node::setTile(Tile *tile) {
   this->tile = tile;
}

char Node::getLetter() const {
   return tile->getLetter();
}
