#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <map>

class Tile {

   const char letter;

public:

   explicit Tile(char);
   Tile(const Tile&);

   int getValue() const;
   char getLetter() const;
};

#endif // ASSIGN2_TILE_H
