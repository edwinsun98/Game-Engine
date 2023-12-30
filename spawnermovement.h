#ifndef SPAWNERMOVEMENT_H
#define SPAWNERMOVEMENT_H
#include <vector>
#include <utility>
#include "movement.h"
#include "subject.h"
#include "model.h"
#include "object.h"
using namespace std;


class SpawnMovement: public Movement, public Subject{
    int startRow = 0;
    int startCol = 0;
    bool spawnOnObject;
    vector<int> spawnObjectIDs; // id numbers of the objects that are spawned during this move
public:
    SpawnMovement(int speed, vector<int> spawnObjectIDs, Model *model, bool spawnOnObject);
    SpawnMovement(const SpawnMovement &other);
    void updatePosition(Object *obj, const int &tickCount) override;
    bool reverseMovement() override;
    const vector<int> &getSpawnObjectIDs();
    bool isSpawnOnObject();
    const int &getStartRow();
    const int &getStartCol();
    ~SpawnMovement() override;
};

#endif
