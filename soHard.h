#ifndef SOHARD_H
#define SOHARD_H

#include "GameState.h"
#include "easyBot.h"

#include <iostream>
#include <algorithm> //so we can use std max n min

int min = -1000;
int max = 1000;

int minimax(GameState& g, int depth, bool turn, int alpha, int beta){
    if(turn){
        int bestScore = min;
        for (int i = 0; i < g.size; i++) {
            for (int j = 0; j < g.size; j++) {
                if (g.grid[i][j] == -1) {
                    g.grid[i][j] = 1; 
                    int score = minimax(g, depth + 1, false, alpha, beta);
                    g.grid[i][j] = -1; 
                    bestScore = std::max(bestScore, score);
                    alpha = std::max(alpha, bestScore);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = max;
        for (int i = 0; i < g.size; i++) {
            for (int j = 0; j < g.size; j++) {
                if (g.grid[i][j] == -1) {
                    g.grid[i][j] = 0; 
                    int score = minimax(g, depth + 1, true, alpha, beta);
                    g.grid[i][j] = -1; 
                    bestScore = std::min(bestScore, score);
                    beta = std::min(beta, bestScore);
                    if (beta <= alpha) {
                        break;
                    }
                }
            }
        }
        return bestScore;
    }
}

Vec findBestMove(GameState game){
    int bestScore = min;
    Vec bestMove;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if(game.grid[i][j] == -1) {
                game.grid[i][j] = 1;
                int score = minimax(game, 0, false, min, max);
                game.grid[i][j] = -1;
                if(score > bestScore){
                    bestScore = score;
                    bestMove.set(i,j);
                }

        }
    }
    return bestMove;
}

//british - the royals r sophisticated; bot playing logic 
void britishBot(){
    GameState game;
    std::cout << "lock in!!" << std::endl;
    while(!game.done){
        std::cout << game << std::endl;
        int x,y;
        
        if(game.currentTurn){
            std::cout << "computer move!!(" << (!game.currentTurn ? "X" : "O") << "):" << std::endl;
            Vec move = findBestMove(game);
            x = move.x;
            y = move.y;
        }else {
            std::cout << "Enter move for (" << (!game.currentTurn ? "X" : "O") << "): ";
            std::cin >> x >> y;

            while(!validInput(x,y)){
                std::cout << game << std::endl << std::endl;
                std::cout << "invalid move !!!! Enter move for (" << (!game.currentTurn ? "X" : "O") << "): ";
                std::cin >> x >> y;
            }
        }

        game.play(x,y);

    }
    system("clear");
    std::cout << game << std::endl;
    if(game.hasWon(0)){
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