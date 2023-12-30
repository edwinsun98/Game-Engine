#include <iostream>
#include "movement.h"
using namespace std;

Movement::Movement(int speed): speed{speed} {}

Movement::Movement(const Movement &other): speed{other.speed} {}

void Movement::updatePosition(Object *obj, const int &tickCount){}

Movement::~Movement(){}
