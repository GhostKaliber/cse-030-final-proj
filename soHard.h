#ifndef SOHARD_H
#define SOHARD_H

#include "GameState.h"
#include "easyBot.h"

#include <iostream>
#include <algorithm> //so we can use max and min, compile w "make force"
                     //std::max n min work without this library, doesnt 
                     //seem to impact logic but ill leave it in

int min_int = -999999999;
int max_int = 999999999;

int eval(GameState game){ //dont actually need this ?
    if(game.hasWon(0)){ // x player, maximizing
        return (game.size-game.turnCount) + 1;
    } else if(game.hasWon(1)) { //o player, minimizing
        return ((game.size-game.turnCount) + 1) * -1;
    } else {
        return 0; //tie condition score
    }
}
//0 = false, 1 = true
//minimax algorithm that simulates moves n assigns score
int minimax(GameState& state, int depth, bool turn)  //depth is look ahead
{
    //if statement could be condensed with a ternary thing for min n max
    int bestScore;

    if(depth >= state.size * state.size || state.done){
        return eval(state);
    }

    if(turn){ //maximizing, X = 0
        bestScore = min_int; //super negative number
        for(int i = 0;i < state.size; i++){
            for (int j = 0; j< state.size; j++){
                if(state.grid[i][j] == -1){
                    //state.grid[i][j] = 0; //hardcoded playing X/0 instead of using currturn
                    GameState cp = state;
                    cp.play(i,j);
                    bestScore = std::max(bestScore, minimax(cp, depth+1, !turn)); //calc score, turn = false
                    //state.grid[i][j] = -1; //reverses move
                }
            }
        }
        return bestScore;
    } else { //minimizing, O = 1
        bestScore = max_int; 
        for (int i = 0; i < state.size; i++){
            for(int j =0; j < state.size; j++){
                if(state.grid[i][j]==-1){
                    //state.grid[i][j] = 1; //hardcoded playing O/1 instead of using currentTurn
                    GameState cp = state;
                    cp.play(i,j);
                    bestScore = std::min(bestScore, minimax(cp, depth+1, !turn));//turn = true
                    //state.grid[i][j] = -1;
                }
            }
        }
        return bestScore;
    }
}



//vec findbestmove - makes use of minimax to find best score
Vec findBestMove(GameState game)
{
    int bestScore = min_int;
    Vec bmove(0,0);
    //bmove.set(-1,-1); //set move to none for now

    for (int i = 0; i < game.size; i++){ //goes thru grid calculating best score w algorithm 
                                         //lowkey could probs condense into one func w minmax
            for(int j = 0; j < game.size; j++){
                if(game.grid[i][j] == -1){ //empty space
                    GameState cp = game;
                    cp.play(i,j);
                    int moveScore = minimax(cp, 0, false);
                    //game.grid[i][j] = -1;
                    if(moveScore > bestScore){
                        bestScore = moveScore;
                        bmove = Vec(i,j);
                        //std::cout << "--" << bmove << std::endl;
                    }
                }
            }
    }
    //std::cout << bmove << std::endl;
    return bmove;
}
//british - the royals r sophisticated; bot playing logic 
void britishBot(){
    GameState game;
    std::cout << "lock in!!" << std::endl;
    while(!game.done){
        std::cout << game << std::endl;
        int x,y;
        
        if(game.currentTurn){ //currentTurn = 1
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
