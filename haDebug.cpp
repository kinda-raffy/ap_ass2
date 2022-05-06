#include<iostream>
#include<string>

#include "Board.h"
#include "LinkedList.h"
#include "Tile.h"
#include "SaveState.h"
#include "Node.h"


int main() {
    std::string saveString = "4 -A-E---G----H---";
    SaveState save = SaveState(saveString);
    Board board = Board(save);
    std::cout << board.toString();
}