#include <iostream>
#include "winlosecondition.h"
using namespace std;

WinLoseCondition::WinLoseCondition(const bool &isWinCondition): isWinCondition{isWinCondition} {}

const bool &WinLoseCondition::getIsWinCondition(){
    return isWinCondition;
}

WinLoseCondition::~WinLoseCondition() {}
