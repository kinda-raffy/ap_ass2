#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"
#include <memory>

class Node {

   // Node object owns tile, but doesn't own next node.
   std::unique_ptr<Tile> tile;
   std::shared_ptr<Node> next;

public:

   /**
    * @brief Construct new node object with a new tile 
    * object corresponding to character arg.
    */
   Node(char);

   /**
    * @brief Construct new node object by moving the supplied tile object.
    * Next pointer will be null by default.
    */
   Node(std::unique_ptr<Tile>);

   /**
    * @brief Construct a new node object by moving the supplied tile object
    * and setting next to the node pointer arg.
    */
   Node(std::unique_ptr<Tile>, std::shared_ptr<Node>);

   /**
    * @brief Construct a new node as a deep copy of the node arg.
    */
   Node(const Node&);

   ~Node() = default;

   // Standard getter and setter.
   std::shared_ptr<Node> getNext();
   void setNext(std::shared_ptr<Node> next);

   /**
    * @brief Get integer value of character in tile field.
    */
   int getValue() const;

   /**
    * @brief Get the character within the tile field.
    */
   char getLetter() const;

   /**
    * @brief Set the owned tile's letter field through node object.
    */
   void setLetter(char);
};

#endif // ASSIGN2_NODE_H
