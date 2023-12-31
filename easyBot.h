#ifndef EASYBOT_H
#define EASYBOT_H

#include "GameState.h"

#include <iostream>
#include <vector>
#include <time.h>

bool validInput(int x, int y){
    if ((x == 0 || x == 1 || x == 2) && (y == 0 || y == 1 || y == 2)) {
        return true;
    } else {
        return false;
    }
}

Vec validMove(GameState game){
    std::vector<Vec> moves;
    for (int i = 0; i < game.size; i++){
        for (int j = 0; j < game.size; j++){
            if (game.grid[i][j] == -1){
                moves.push_back(Vec(i, j));
            }
        }
    }
    srand(time(NULL));
    int index = rand() % moves.size();
    try{ //to lmk if smth is buggy
        return moves.at(index);
    } catch (const std::out_of_range& e) { 
        std::cout << "index " << index << " out of range :(" << std::endl;
    }
    return Vec(0, 0); //avoid warning abt not returning anything
}

void easyBot(){
    GameState game;
    std::cout << "light work" << std::endl;
    while(!game.done){

        std::cout << game << std::endl;

        int x,y;

        if(game.currentTurn){
            std::cout << "Computer's move: (" << (!game.currentTurn ? "X" : "O") << ")" << std::endl;
            Vec move = validMove(game);
            x = move.x;
            y = move.y;
        }else{

            std::cout << std::endl;
            std::cout << "Enter move for (" << (!game.currentTurn ? "X" : "O") << "): ";
            std::cin >> x >> y;

            while(!validInput(x,y)) {
                std::cout << game << std::endl;

                std::cout << std::endl;
                std::cout << "Invalid move. Enter move for (" << (!game.currentTurn ? "X" : "O") << "): ";
                std::cin >> x >> y;
            }
        }
        
    game.play(x,y);
    }
    system("clear");
            std ::cout << game << std ::endl;
            std::cout << std::endl;
        if ( game.hasWon(0)) {
            std :: cout << "X Wins" << std :: endl;
        
        } else if (game.hasWon(1)) {
            std :: cout << "O Wins" << std :: endl;
        
        } else{
            std :: cout << "Tie" << std :: endl;
        }
        std::cout << std::endl;
        std::cout << "Press [enter] to return to main menu" << std::endl;
        std::cin.ignore(9999999, '\n');
        std::cin.get();       
}
#endif
