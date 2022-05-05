#include "Node.h"

Node::Node(char letter)
   : Node {std::move(std::make_unique<Tile>(letter))} {
}

Node::Node(std::unique_ptr<Tile> tile)
   : Node {std::move(tile), nullptr} {
}

Node::Node(std::unique_ptr<Tile> tile, std::shared_ptr<Node> next) 
   : tile {std::move(tile)}, next {next} {
}

Node::Node(const Node &source)
   : tile {new Tile {source.getLetter()}}, next {nullptr} {
   // Next node is currently not deep copied. 
}

// Return a shared pointer to the next node.
std::shared_ptr<Node> Node::getNext() {
   return next;
}

// Set next pointer to a new node. Smart pointers will handle memory.
void Node::setNext(std::shared_ptr<Node> next) {
   this->next = next;
}

char Node::getLetter() const {
   return tile->getLetter();
}

void Node::setLetter(char letter) {
   tile->setLetter(letter);
}

int Node::getValue() const {
   return tile->getValue();
}
