#include<iostream>
#include<string>

//#include "Board.h"
#include "LinkedList.h"
#include "Tile.h"
#include "SaveState.h"
#include "Node.h"


int main() {
    std::string testString = "A-1, B-3, Z-6, D-6";
    LinkedList testList(testString);
    std::cout << testList.toString();
}
