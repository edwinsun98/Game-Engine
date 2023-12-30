#include <iostream>
#include "typecountwinlose.h"
using namespace std;

TypeCountWinLose::TypeCountWinLose(const bool &isWinCondition, 
                                const vector<pair<int,int>> &conditionPairs):
                                WinLoseCondition{isWinCondition}, conditionPairs{conditionPairs} {}

bool TypeCountWinLose::conditionsMet(Board *board){
    size_t counter = 0;
    for(auto &p : conditionPairs){
        if(board->countTypes(p.second) == p.first){
            ++counter;
        }
    }
    // if all the conditions are met, then return true
    return (counter == conditionPairs.size());
}

TypeCountWinLose::~TypeCountWinLose() {}
