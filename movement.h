#ifndef MOVEMENT_H
#define MOVEMENT_H
#include "reversible.h"
class Object;

class Movement: public Reversible{
protected:
    int speed; // the number of ticks before this movement will trigger again 
public:
    Movement(int speed);
    Movement(const Movement &other);
    virtual void updatePosition(Object *obj, const int &tickCount) = 0;
    virtual ~Movement() = 0;
};
#endif
