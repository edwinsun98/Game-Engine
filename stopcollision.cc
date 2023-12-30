#include <iostream>
#include "stopcollision.h"
using namespace std;

StopCollision::StopCollision(): Collision{} {}

void StopCollision::handleCollision(Object *a, Object *b){
    // restores the most recent position a and b were at prior to getting into the collision
    a->restorePosition();
    b->restorePosition();
}

StopCollision::~StopCollision(){}
