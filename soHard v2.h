#ifndef SOHARD_H
#define SOHARD_H

#include "GameState.h"
#include "easyBot.h"

#include <iostream>
#include <algorithm> //so we can use "std::max"

int min_int = -999999999;
int max_int = 999999999;

//minimax algorithm that simulates moves n assigns score
int minimax(GameState state, int depth, bool turn)
{
    if(depth > 50){ //amount of moves to look at
        std::cout << "depth reached:" << depth << std::endl;
        return 0;
    }
    int bestScore;

    if(turn){
        bestScore = min_int; //super negative number
        for(int i = 0;i <state.size; i++){
            for (int j = 0; j<state.size; j++){
                if(state.grid[i][j] == -1){
                    state.grid[i][j] = 1; //play move
                    int t_score = minimax(state, depth+1, false); //calc score
                    state.grid[i][j] = -1; //reverses move
                    bestScore = std::max(bestScore, t_score); //get max score
                }
            }
        }
    } else {
        bestScore = max_int; 
        for (int i = 0; i < state.size; i++){
            for(int j =0; j < state.size; j++){
                if(state.grid[i][j]==-1){
                    state.grid[i][j] = 0;
                    int t_score = minimax(state, depth+1, true);
                    state.grid[i][j] = -1;
                    bestScore = std::min(bestScore, t_score);
                }
            }
        }
    }
    return bestScore;
}



//vec findbestmove - makes use of minimax to find best score
Vec findBestMove(GameState game)
{
    int bestScore = min_int;
    Vec bmove;
    bmove.set(-1,-1); //set move to none for now

    for (int i = 0; i < game.size; i++){ //goes thru grid calculating best score w algorithm 
                                         //lowkey could probs condense into one func w minmax
            for(int j =0; j < game.size; j++){
                if(game.grid[i][j] == -1){ //empty space
                    game.play(i,j);
                    int moveScore = minimax(game, 0, game.currentTurn);
                    game.grid[i][j] = -1;
                    if(moveScore > bestScore){
                        bestScore = moveScore;
                        bmove.set(i,j);
                    }
                }
            }
    }
    std::cout << bmove << std::endl;
    return bmove;
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
