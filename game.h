#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "easyBot.h"
#include "soHard.h"
#include <iostream>

void printMenu() {
    system("clear");
    std :: cout << "Welcome to Tic-Tac-Toe\n" << std :: endl;
    std :: cout << "  1. PLay against the computer" << std :: endl;
    std :: cout << "  2. Play against a human opponent" << std :: endl;
    std :: cout << "  3. Settings" << std :: endl;
    std :: cout << "  4. Exit\n" << std :: endl;
    std :: cout << "Enter choice: ";    
}

void humanOpponent(GameState game) {
    int x, y;
    std ::cout << game << std ::endl;
    while (!game.done) {
            std :: cout << "What is your move?" << std ::endl;
            std ::cin >> x >> y;
            game.play(x,y);
            system("clear");
            std ::cout << game << std ::endl;  
        if ( game.hasWon(0)) {
            std :: cout << "X Wins" << std :: endl;
            break;
        } else if (game.hasWon(1)) {
            std :: cout << "O Wins" << std :: endl;
            break;
        } else if (game.done) {
            std :: cout << "Tie" << std :: endl;
        }
    }

    std :: cout << "Press [Enter] to return to the main menu" << std :: endl;
    std :: cin.ignore();
    std :: cin.ignore();
}

int settings() {
    std :: cout << "Change difficulty of the computer" << std :: endl;
    std :: cout << "1 - Easy Mode " << std :: endl;
    std :: cout << "2 - Hard Mode " << std :: endl;
    std :: cout << "Enter Choice: ";
    int choice;
    std :: cin >> choice;
    return choice;
}

void runGame(GameState game) {
    int difficulty = 1;
    system("clear");
    printMenu();
    int input; 
    std :: cin >> input;

    while ( input != 4 ) {
    if (input == 1) {
        if ( difficulty == 1 ) {
            system("clear");
            easyBot();
        } else if (difficulty == 2) {
            system("clear");
            britishBot();
        }
    } else if (input == 2) {
        system("clear");
        humanOpponent(game);
    } else if (input == 3) {
        system("clear");
        difficulty = settings();
    }
        printMenu();
        std :: cin >> input;
    }

    system("clear");
    std :: cout << "GOODBYE" << std :: endl;
}
#endif