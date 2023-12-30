#ifndef ONEWAYDAMAGE_H
#define ONEWAYDAMAGE_H
#include "collision.h"
#include "object.h"
using namespace std;

class OneWayDamage: public Collision{
    string healthAttribute;
    string damageAttribute;
public:
    OneWayDamage(string healthAttribute, string damageAttribute);
    void handleCollision(Object *a, Object *b) override;
    ~OneWayDamage() override;
};

#endif
