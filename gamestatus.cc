#include <iostream>
#include "gamestatus.h"
using namespace std;

GameStatus::GameStatus(): StatusLine{} {}

string GameStatus::getStatus(Board *board){
    BoardState s = board->getBoardState();
    if(s == BoardState::Running){
        return "Game Running";
    }else if(s == BoardState::Lost){
        return "You Lost";
    }else if(s == BoardState::Won){
        return "You Won";
    }
    return "";
}

GameStatus::~GameStatus(){}
