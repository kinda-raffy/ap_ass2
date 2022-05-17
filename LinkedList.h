#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <memory>
#include <regex>
#include <iostream>
#include <string>
#include <sstream>

class LinkedList {

   std::shared_ptr<Node> head;
   std::shared_ptr<Node> tail;
   std::size_t length;

public:

   /**
    * @brief Construct an empty linked list object.
    */
   LinkedList();

   /**
    * @brief Construct a linked list from a string.
    * Only works if the linked list string is in the correct format.
    */
   LinkedList(const std::string&);

   /**
    * @brief Construct a copy of another linked list object.
    */
   LinkedList(const LinkedList&);

   ~LinkedList() = default;

   /**
    * @brief Delete and return the character at the front of the list.
    * @return char Letter that was at the front of the list.
    */
   char pop();

   /**
    * @brief Delete the first occurance of the specified character in the list.
    * @return true The character was in the list and has been deleted.
    * @return false Character did not occur in list.
    */
   bool remove(char);

   /**
    * @brief Add the supplied character arg to the end of the list.
    */
   void append(char);

   /**
    * @brief Add the provided tile to the end of the list by moving pointer.
    * Vestigial from early stages, not used directly anywhere since tiles and
    * nodes were made the almost exclusive purview of linked list objects.
    */
   void append(std::unique_ptr<Tile>);

   /**
    * @brief Check if the current linked list contains and instance of the 
    * supplied character arg.
    * @return true Character occurs in list.
    * @return false Character does not occur in list.
    */
   bool contains(char) const;

   /**
    * @brief Find the first occurance of the first arg and replace with second.
    * @return true 
    * @return false 
    */
   bool replace(char, char);

   /**
    * @brief Returns the size of the list.
    * @return std::size_t Size of list.
    */
   std::size_t size() const;

   /**
    * @brief Converts current linked list object into its string representation.
    * @return std::string The string corresponding with current list state.
    */
   std::string toString() const;

   /**
    * @brief Verifies that the string arg is in valid linked list layout.
    * @return true Regex validation checks passed.
    * @return false Regex validation checks failed.
    */
   static bool validateListString(const std::string&);
};

#endif // ASSIGN2_LINKEDLIST_H
