#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <utility>
#include <map>
#include "model.h"
#include "view.h"
#include "object.h"
#include "movement.h"
#include "collision.h"
#include "ncurseskeyinput.h"
#include "wasdmovement.h"
#include "endgamecollision.h"
#include "spawnermovement.h"
#include "bitmapobject.h"
#include "basicobject.h"
#include "rectangleobject.h"
#include "statusline.h"
#include "spawnercollision.h"
#include "winlosecondition.h"
using namespace std;

enum class BorderCollisionType { Solid, View };

enum class BoardState {Won, Lost, Running};

class Board: public Model{
    BoardState state = BoardState::Running;
    int rows;
    int cols;
    vector<Object*> theObjects;
    vector<Object*> spawnerObjects;
    vector<Object*> spawnedObjectsQueue; // used to temporarily store all
                                         // spawned objects on the current tick
    vector<Movement*> playerControlledMovements;
    map<int,vector<pair<int,Collision*>>> collisionMap;
    BorderCollisionType borderType;
    vector<StatusLine*> statusLines;
    vector<WinLoseCondition*> winLoseConditions;

    // private methods
    bool intersect(vector<pair<int,int>> a, vector<pair<int,int>> b);
    size_t countOutsideBorder(const vector<pair<int,int>> &points) const;
    void addSpawnedObjects();
    void handleMoves(const int &tickCount);
    void handleSpawn(const vector<int> &spawnIDs, const bool &isSpawnAtEvent, 
                        const int &startRow, const int &startCol);
    void handleBorderCollision(const vector<pair<int,int>> &objectPoints, 
                                    const int &objectIndex, const int &borderIndex);
    void handleCollisions();
    void handleDespawn();
    void processCollisionPairHelper(const int &aIndex, const int &bIndex);
    void processCollisionPair(const int &aIndex, const int &bIndex);
    void addMovementHelper(const int &id, Movement *movement, const bool &playerControlled, 
                            vector<Object*> &vec);
    void handleWinLoseConditions();
public:
    Board(const int &rows, const int &cols);
    BoardState getBoardState() const;
    int countTypes(const int &type) const;
    int getAttribute(const int &id, const string &attributeName) const;
    int numWinLoseConditions() const;
    void addView(View *view) override;
    void notify(Subject *whofrom) override;
    void processTick(const int &tickCount);
    void drawAll(); // for objects
    void drawStatusLines(); // for status lines
    void addObject(Object *object);
    void addToSpawnQueue(Object *object);
    void addSpawnerObject(Object *object);
    void addControlledMovement(Movement *movement);
    void addMovement(const int &id, Movement *movement, const bool &playerControlled);
    void addCollision(const int &typeA, const int &typeB, Collision *collision);
    void addAttribute(const int &id, const string &name, const int &value);
    void setBorderType(BorderCollisionType type);
    void addStatusLine(StatusLine *line);
    void addWinLoseCondition(WinLoseCondition *winLoseCondition);
    ~Board() override;
};

#endif
