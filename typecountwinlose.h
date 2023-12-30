#ifndef TYPECOUNTWINLOSE_H
#define TYPECOUNTWINLOSE_H
#include <vector>
#include <utility>
#include "board.h"
#include "winlosecondition.h"
using namespace std;

class TypeCountWinLose: public WinLoseCondition{
    vector<pair<int,int>> conditionPairs; // pairs of {value, type}
public:
    TypeCountWinLose(const bool &isWinCondition, const vector<pair<int,int>> &conditionPairs);
    bool conditionsMet(Board *board) override; // checks if the number of objects with the specified type
                                               // equals to the specified value count, for all pairs
    ~TypeCountWinLose() override;
};

#endif
