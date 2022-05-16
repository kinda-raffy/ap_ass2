#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <map>
#include <cctype>

class Tile {

   char letter;

public:

   explicit Tile(char);
   Tile(const Tile&);
   ~Tile() = default;

   int getValue() const;
   char getLetter() const;
   void setLetter(char);

   static int getTileValue(char);
};

#endif // ASSIGN2_TILE_H
