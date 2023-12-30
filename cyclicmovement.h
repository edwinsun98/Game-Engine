#ifndef CYCLICMOVEMENT_H
#define CYCLICMOVEMENT_H
#include <vector>
#include <tuple>
#include "movement.h"
using namespace std;

class CyclicMovement: public Movement{
    vector<vector<tuple<int,int,char>>> forms; // the forms at each cycle represented by 
                                               // vector<tuple<int,int,char>> in which this
                                               // movement cycles through
    
    int cycleNumber = 0;
public:
    CyclicMovement(int speed, vector<vector<tuple<int,int,char>>> forms);
    CyclicMovement(const CyclicMovement &other);
    void updatePosition(Object *obj, const int &tickCount) override;
    bool reverseMovement() override;
    ~CyclicMovement() override;
};

#endif
