#include <iostream>
#include "spawnercollision.h"
using namespace std;

SpawnerCollision::SpawnerCollision(vector<int> spawnObjectIDs, Model *model, bool spawnOnCollision):
                                Collision{}, Subject{}, spawnOnCollision{spawnOnCollision}, 
                                spawnObjectIDs{spawnObjectIDs} {
    attach(model);
}

void SpawnerCollision::handleCollision(Object *a, Object *b){
    if(spawnOnCollision){ // updates the center of a and b's collision to spawn the new object at
        pair<int,int> acenter = a->getCenter();
        pair<int,int> bcenter = b->getCenter();
        startRow = (acenter.first+bcenter.first)/2;
        startCol = (acenter.second+bcenter.second)/2;
    }
    notifyObservers();
}

const vector<int> &SpawnerCollision::getSpawnObjectIDs(){
    return spawnObjectIDs;
}

bool SpawnerCollision::isSpawnOnCollision(){
    return spawnOnCollision;
}

const int &SpawnerCollision::getStartRow(){
    return startRow;
}

const int &SpawnerCollision::getStartCol(){
    return startCol;
}

SpawnerCollision::~SpawnerCollision(){}
