#include "LinkedList.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <random>

#define EXIT_SUCCESS    0
#define EXIT_FAILURE    1

void shuffleArray(const std::vector<char>& letters) {
    auto eng = std::default_random_engine{};
    std::shuffle(letters.begin(), letters.end(), eng);
}

auto* readBaseTileBag() {
    std::ifstream file;
    file.open("ScrabbleTiles.txt");
    if(!file.is_open()) { throw std::runtime_error("Could not open tile bag file"); }

    auto* charList = new LinkedList();
    std::string line;
    while(std::getline(file, line)) { charList->append(line[0]); }
    file.close();
    return charList;
}

int createTileBag(const std::string &filename="") {

}

LinkedList* createHand(const std::string &fileName="") {
    auto *hand = new LinkedList();

    if (fileName.empty()) {
        // TODO: Create a random hand
    } else {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << fileName << std::endl;
            return nullptr;
        }
        std::string line;
        while (std::getline(file, line)) {
            if (!(line.empty()) and line[1] == '-' and line[3] != ',') {
                auto *hand = new LinkedList();
                // FIXME - Spilt string into letter and pair values
                // auto *tile = new Tile(line);
                // hand->append(tile);
            }
        }
        file.close();
    }
    return hand;
}

// FIXME - Placeholder function
//int createBoard(const void *board=nullptr);

// TODO: Make player a class? YES PLEASE RAF PLEASE MAKE A PLAYER CLASS ON GOD
// FIXME: Create classes automatically handles load and new games. Update parameters to match.
void generateGame(const std::string& player1Name,
                  const std::string& player2Name,
                  int player1Score=-1,
                  int player2Score=-1,
                  const void *player1Hand=createHand(),
                  const void *player2Hand=createHand(),
                  const int board=createBoard(),
//                  const int tileBag=createTileBag(),
                  const std::string& currPlayer="") {
    if (currPlayer.empty()) {
        // New game.
    } else {
        // Load game from file.
    }
}

void credits() {
    std::cout
        << "-----------------------------------\n"
        // Raf
        << "Name: Rafat Mahiuddin\n"
        << "Student ID: s3897093\n"
        << "Email: s3897093@student.rmit.edu.au\n\n"
        // Adrian
        << "Name: Adrian Louis Rebellato\n"
        << "Student ID: s3889401\n"
        << "Email: s3889401@student.rmit.edu.au\n\n"
        // Harry
        << "Name: Harry Porter\n"
        << "Student ID: s3888604\n"
        << "Email: s3888604@student.rmit.edu.au\n\n"
        // Alexander
        << "Name: Alexander Mitchell\n"
        << "Student ID: s3902255\n"
        << "Email: s3902255@student.rmit.edu.au\n\n";
}


int validFile(const std::string& fileName) {
    int returnStatus = EXIT_SUCCESS;
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cout << "File " << fileName << " not found" << std::endl;
        returnStatus = EXIT_FAILURE;
    }
    file.close();
    // TODO - check file format
    return returnStatus;
}

void loadGame() {
    std::cout << "Enter the filename from which load a game" << std::endl;
    std::string filename;
    std::cin >> filename;
    if (validFile(filename)) {
        std::cout << "Scrabble game successfully loaded" << std::endl;
        // TODO - load game
    }
}

std::string getPlayerName(int num) {
    std::string playerName;
    std::cout << "Enter a name for player "
        << num << " (uppercase characters only)" << std::endl;
    std::cin >> playerName;
    while (!(std::all_of(playerName.begin(), playerName.end(), isupper))) {
        std::cout << "Invalid name. Please enter a name for player "
            << num << " (uppercase characters only)" << std::endl;
        std::cin >> playerName;
    }
    return playerName;
}

//void newGame() {
//    std::cout << "Starting a New Game" << std::endl;
//    std::string player1Name = getPlayerName(1);
//    std::string player2Name = getPlayerName(2);
//    std::cout << "Let's Play" << std::endl;
//    generateGame(player1Name, player2Name);
//}


int gameModeHandler() {
    int choice;
    std::cout << "1. New Game\n";
    std::cout << "2. Load Game\n";
    std::cout << "3. Credits (Show student information)\n";
    std::cout << "4. Quit\n";
    std::cin >> choice;
    return choice;
}

void gameHandler() {
    int choice = gameModeHandler();
    if (choice == 1) {
        newGame();
    } else if (choice == 2) {
        loadGame();
    } else if (choice == 3) {
        credits();
        // Re-display menu.
        gameModeHandler();
    } else if (choice == 4) {
        std::cout << "Goodbye" << std::endl;
    } else {
        std::cout << "Invalid choice" << std::endl;
    }
}


void greet() {
   std::cout << "Welcome to Scrabble!\n";
   std::cout << "--------------------" << std::endl;
}



int main() {
    greet();
    gameModeHandler();

    return EXIT_SUCCESS;
}
