#ifndef SPAWNERCOLLISION_H
#define SPAWNERCOLLISION_H
#include "collision.h"
#include "object.h"
#include "model.h"
#include "subject.h"
using namespace std;

class SpawnerCollision: public Collision, public Subject{
    int startRow = 0;
    int startCol = 0;
    bool spawnOnCollision; // true if the new objects spawn directly on the collision point
    vector<int> spawnObjectIDs; // id numbers of the objects that are spawned during this move
public:
    SpawnerCollision(vector<int> spawnObjectIDs, Model *model, bool spawnOnCollision);
    void handleCollision(Object *a, Object *b) override;
    const vector<int> &getSpawnObjectIDs();
    bool isSpawnOnCollision();
    const int &getStartRow();
    const int &getStartCol();
    ~SpawnerCollision() override;
};

#endif
