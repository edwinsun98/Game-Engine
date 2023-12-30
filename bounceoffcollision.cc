#include <iostream>
#include "bounceoffcollision.h"
using namespace std;

BounceOffCollision::BounceOffCollision(): Collision{} {}

void BounceOffCollision::handleCollision(Object *a, Object *b){
    // reverses the direction of both object a's and object b's movements
    a->reverseMovements();
    b->reverseMovements();
}

BounceOffCollision::~BounceOffCollision(){}
