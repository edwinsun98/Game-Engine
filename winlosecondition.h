#ifndef WINLOSECONDITION_H
#define WINLOSECONDITION_H
using namespace std;

class Board;

class WinLoseCondition{
    bool isWinCondition; // true if this condition leads to a win and false if it leads to a loss
public:
    WinLoseCondition(const bool &isWinCondition);
    virtual bool conditionsMet(Board *board) = 0;
    const bool &getIsWinCondition();
    virtual ~WinLoseCondition();
};

#endif
