#ifndef COLLISION_H
#define COLLISION_H
#include "object.h"
using namespace std;

class Collision{
public:
    Collision();
    virtual void handleCollision(Object *a, Object *b) = 0;
    virtual ~Collision() = 0;
};

#endif
