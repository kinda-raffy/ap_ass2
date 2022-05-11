#include "LinkedList.h"
#include "SaveState.h"
#include "Core.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <random>
#include <memory>

#define EXIT_SUCCESS    0
#define EXIT_FAILURE    1


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
              << num
              << " (uppercase characters only)" << std::endl;
    std::cin >> playerName;
    while (!(std::all_of(playerName.begin(), playerName.end(), isupper))) {
        std::cout << "Invalid name. Please enter a name for player "
                  << num
                  << " (uppercase characters only)" << std::endl;
        std::cin >> playerName;
    }
    return playerName;
}

void newGame() {
    std::vector<std::string> playerNames(2);
    std::cout << "Starting a New Game\n" << std::endl;
    playerNames[0] = getPlayerName(1);
    playerNames[1] = getPlayerName(2);
    std::cout << "\nLet's Play\n" << std::endl;
    Core game(playerNames);
    game.runGame();
}


int gameModeHandler() {
    int choice;
    std::cout << "1. New Game\n";
    std::cout << "2. Load Game\n";
    std::cout << "3. Credits (Show student information)\n";
    std::cout << "4. Quit\n" << std::endl;
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
        gameHandler();
    } else if (choice == 4 || choice == 0) { // Choice = 0 when EOF
        std::cout << "Goodbye" << std::endl;
    } else {
        std::cout << "Invalid choice" << std::endl;
        gameHandler();
    }
}


void greet() {
   std::cout << "Welcome to Scrabble!\n";
   std::cout << "--------------------" << std::endl;
}



int main() {
    greet();
    gameHandler();

    return EXIT_SUCCESS;
}
