#include "Node.h"

Node::Node(char letter)
   : Node {std::move(std::make_unique<Tile>(letter))} {
}

Node::Node(std::unique_ptr<Tile> tile)
   : Node {std::move(tile), nullptr} {
}

Node::Node(std::unique_ptr<Tile> tile, std::shared_ptr<Node> next) 
   : tile {std::make_unique<Tile>(tile)}, next {next} {
}

Node::Node(const Node &source)
   : tile {new Tile {source.getLetter()}}, next {nullptr} {
   // Next node is currently not deep copied. 
}

Node::~Node() {
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
