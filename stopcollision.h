#ifndef STOPCOLLISION_H
#define STOPCOLLISION_H
#include "collision.h"
#include "object.h"
using namespace std;

class StopCollision: public Collision{
public:
    StopCollision();
    void handleCollision(Object *a, Object *b) override;
    ~StopCollision() override;
};

#endif
