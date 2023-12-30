#ifndef BOUNCEOFFCOLLISION_H
#define BOUNCEOFFCOLLISION_H
#include "collision.h"
#include "object.h"
using namespace std;

class BounceOffCollision: public Collision{
public:
    BounceOffCollision();
    void handleCollision(Object *a, Object *b) override;
    ~BounceOffCollision() override;
};

#endif
