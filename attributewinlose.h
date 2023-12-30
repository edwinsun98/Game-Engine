#ifndef ATTRIBUTEWINLOSE_H
#define ATTRIBUTEWINLOSE_H
#include <vector>
#include <tuple>
#include "board.h"
#include "winlosecondition.h"
using namespace std;

class AttributeWinLose: public WinLoseCondition{
    vector<tuple<int,int,string>> conditionTuples; // tuples of {value, id, attribute name}
public:
    AttributeWinLose(const bool &isWinCondition, const vector<tuple<int,int,string>> &conditionTuples);
    bool conditionsMet(Board *board) override; // checks if all tuples in conditionTuples have that 
                                               // value equals the attribute associated with id and name
    ~AttributeWinLose() override;
};

#endif
