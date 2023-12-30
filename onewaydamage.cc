#include <iostream>
#include "onewaydamage.h"
using namespace std;

OneWayDamage::OneWayDamage(string healthAttribute, string damageAttribute): Collision{}, 
                                                                            healthAttribute{healthAttribute},
                                                                            damageAttribute{damageAttribute}{}

void OneWayDamage::handleCollision(Object *a, Object *b){ // when object a damages object b
    b->setAttribute(healthAttribute, max(0, (b->getAttribute(healthAttribute))-(a->getAttribute(damageAttribute))));
    if((b->getAttribute(healthAttribute)) <= 0){ // despawn object b if health reaches 0 or below
        b->setForcedDespawn(true);
    }
}

OneWayDamage::~OneWayDamage(){}
