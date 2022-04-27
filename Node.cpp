#include "Node.h"

Node::Node(std::unique_ptr<Tile> tile, std::shared_ptr<Node> next) 
   : tile {std::make_unique<Tile>(tile)}, next {next} {
}

Node::Node(const Node &source)
   : tile {new Tile {source.getLetter()}}, next {nullptr} {
   // TODO: Should next be deep copied as well?
}

Node::~Node() {
   // Node object has ownership of tile, but not of next node.
   // delete tile;
}

std::shared_ptr<Node> Node::getNext() {
   return next;
}

void Node::setNext(std::shared_ptr<Node> next) {
   // Nodes do not own the next node pointed to; do not delete next.
   this->next = next;
}

std::unique_ptr<Tile> Node::getTile() {
   return std::make_unique<Tile>(tile);
}

void Node::setTile(std::unique_ptr<Tile> tile) {
   // Deacollate storage of unused tile.
   // delete this->tile;
   this->tile = std::make_unique<Tile>(tile);
}

char Node::getLetter() const {
   return tile->getLetter();
}
