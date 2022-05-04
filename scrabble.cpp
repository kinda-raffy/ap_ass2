#include "LinkedList.h"

#include <iostream>
#include <algorithm>
#include <fstream>

#define EXIT_SUCCESS    0
#define EXIT_FAILURE    1


int credits() {
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
    return EXIT_SUCCESS;
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


int loadGame() {
    std::cout << "Enter the filename from which load a game" << std::endl;
    std::string filename;
    std::cin >> filename;
    if (validFile(filename)) {
        std::cout << "Scrabble game successfully loaded" << std::endl;
        // TODO - load game
    }
    return EXIT_SUCCESS;
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


int newGame() {
    std::cout << "Starting a New Game" << std::endl;
    std::string player1Name = getPlayerName(1);
    std::string player2Name = getPlayerName(2);
    std::cout << "Let's Play" << std::endl;
    // TODO - create a new game
    std::cout << "Player 1: " << player1Name << std::endl;
    std::cout << "Player 2: " << player2Name << std::endl;
    return EXIT_SUCCESS;
}


int menu() {
    int choice;
    std::cout << "1. New Game\n";
    std::cout << "2. Load Game\n";
    std::cout << "3. Credits (Show student information)\n";
    std::cout << "4. Quit\n";
    std::cin >> choice;
    return choice;
}


void gameHandler() {
    int choice = menu();
    if (choice == 1) {
        newGame();
    } else if (choice == 2) {
        loadGame();
    } else if (choice == 3) {
        credits();
        // Re-display menu.
        gameHandler();  // FIXME - can this lead to errors?
    } else if (choice == 4) {
        std::cout << "Goodbye" << std::endl;
    } else {
        std::cout << "Invalid choice" << std::endl;
    }
}


void greet() {
   std::cout << "Welcome to Scrabble!\n";
   std::cout << "-------------------" << std::endl;
}


int main() {
    greet();
    gameHandler();

    auto* list = new LinkedList();
    delete list;

    std::cout << "TODO: Implement Scrabble!" << std::endl;

    return EXIT_SUCCESS;
}
