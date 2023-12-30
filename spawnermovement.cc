#include <iostream>
#include "spawnermovement.h"
using namespace std;

SpawnMovement::SpawnMovement(int speed, vector<int> spawnObjectIDs, Model *model,
                                bool spawnOnObject): 
        Movement{speed}, Subject{}, spawnOnObject{spawnOnObject}, spawnObjectIDs{spawnObjectIDs}{
        attach(model);
}

SpawnMovement::SpawnMovement(const SpawnMovement &other): 
                                        Movement{other}, Subject{other}, 
                                        spawnOnObject{other.spawnOnObject},
                                        spawnObjectIDs{other.spawnObjectIDs}{
    startRow = other.startRow;
    startCol = other.startCol;
}

void SpawnMovement::updatePosition(Object *obj, const int &tickCount){
    if(tickCount%speed == 0){
        if(spawnOnObject){ // updates the center of obj's position as the place to spawn the
                           // new object at
            auto pos = obj->getCenter();
            startRow = pos.first;
            startCol = pos.second;
        }
        notifyObservers();
    }
}

bool SpawnMovement::reverseMovement(){
    return 0;
}

const vector<int> &SpawnMovement::getSpawnObjectIDs(){
    return spawnObjectIDs;
}

bool SpawnMovement::isSpawnOnObject(){return spawnOnObject;}

const int &SpawnMovement::getStartRow(){return startRow;}

const int &SpawnMovement::getStartCol(){return startCol;}

SpawnMovement::~SpawnMovement(){}
