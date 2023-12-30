#ifndef STRAIGHTMOVEMENT_H
#define STRAIGHTMOVEMENT_H
#include "movement.h"
using namespace std;

class StraightMovement: public Movement{
    int rowChange;
    int colChange;
public:
    StraightMovement(int speed, int rowChange, int colChange);
    StraightMovement(const StraightMovement &other);
    void updatePosition(Object *obj, const int &tickCount) override;
    bool reverseMovement() override;
    ~StraightMovement() override;
};

#endif
