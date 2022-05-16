#include "SaveState.h"
#include "Core.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>

// Only prototypes for entry / print functions included; add rest if required.
void greet();
void credits();
void handleSelection();

int main() {
    greet();
    handleSelection();
    return EXIT_SUCCESS;
}

std::string readPlayerName(int playerIndex) {
    std::string playerName;
    // Retrieve user input for player name and specify requirements.
    std::cout 
        << "Enter a name for player " << playerIndex 
        << " (uppercase characters only)\n" << "> ";
    std::cin >> playerName;
    // Whilst input does not fulfill requirements, continue retrieving input.
    while (!(std::all_of(playerName.begin(), playerName.end(), isupper))) {
        std::cout 
            << "Invalid name. Please enter a name for player " << playerIndex 
            << " (uppercase characters only)\n" << "> ";
        std::cin >> playerName;
    }
    return playerName;
}

void createNewCore() {
    std::vector<std::string> players {};
    std::cout << "\nStarting a New Game\n\n";
    players.push_back(readPlayerName(1));
    players.push_back(readPlayerName(2));
    std::cout << "\nLet's Play!\n";
    auto core {std::make_unique<Core>(players)};
    core->runCore();
}

void loadSavedCore() {
    // Retrieve input specifying file to be loaded.
    std::cout << "Enter the filename from which load a game\n";
    std::string file {};
    std::cout << "> ";
    std::cin >> file;
    // Read saved data, then create and run core object.
    auto load {std::make_unique<SaveState>(file)};
    auto core {std::make_unique<Core>(*load)};
    core->runCore();
}

int selectMode() {
    std::string choice;
    std::cout 
        << "1. New Game\n"
        << "2. Load Game\n"
        << "3. Credits (Show student information)\n"
        << "4. Quit\n\n"
        << "> ";
    std::getline(std::cin >> std::ws, choice);
    return std::stoi(choice);
}

void handleSelection() {
    bool quit {false};
    while (!quit) {
        int choice {selectMode()};
        if (choice == 1) {
            createNewCore();
            quit = true;
        } else if (choice == 2) {
            loadSavedCore();
            quit = true;
        } else if (choice == 3) {
            credits();
        } else if (choice == 4 || std::cin.eof()) {
            std::cout << "Goodbye\n";
            quit = true;
        } else {
            std::cout << "Invalid choice\n";
        }
    }
}

void greet() {
   std::cout << "Welcome to Scrabble!\n";
   std::cout << "--------------------\n";
}

void credits() {
    std::cout
        << "-----------------------------------\n"
        << "Name: Rafat Mahiuddin\n"
        << "Student ID: s3897093\n"
        << "Email: s3897093@student.rmit.edu.au\n\n"
        << "Name: Adrian Louis Rebellato\n"
        << "Student ID: s3889401\n"
        << "Email: s3889401@student.rmit.edu.au\n\n"
        << "Name: Harry Porter\n"
        << "Student ID: s3888604\n"
        << "Email: s3888604@student.rmit.edu.au\n\n"
        << "Name: Alexander Mitchell\n"
        << "Student ID: s3902255\n"
        << "Email: s3902255@student.rmit.edu.au\n"
        << "-----------------------------------\n";
}
