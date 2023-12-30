#include <iostream>
#include "attributewinlose.h"
using namespace std;

AttributeWinLose::AttributeWinLose(const bool &isWinCondition, 
                                const vector<tuple<int,int,string>> &conditionTuples):
                                WinLoseCondition{isWinCondition}, conditionTuples{conditionTuples} {}

bool AttributeWinLose::conditionsMet(Board *board){
    size_t counter = 0;
    for(auto &p : conditionTuples){
        if(board->getAttribute(get<1>(p), get<2>(p)) == get<0>(p)){
            ++counter;
        }
    }
    return (counter == conditionTuples.size());
}

AttributeWinLose::~AttributeWinLose() {}
