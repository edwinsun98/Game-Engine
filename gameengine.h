#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include <vector>
#include "view.h"
#include "controller.h"
#include "ncursesview.h"
#include "ncurseskeyinput.h"
#include "board.h"
#include "movement.h"
#include "wasdmovement.h"
#include "collision.h"
#include "stopcollision.h"
#include "onewaydamage.h"
#include "bounceoffcollision.h"
#include "borderobject.h"
#include "bordermovement.h"
#include "endgamecollision.h"
#include "cyclicmovement.h"
#include "straightmovement.h"
#include "bitmapobject.h"
#include "basicobject.h"
#include "rectangleobject.h"
#include "spawnermovement.h"
#include "statusline.h"
#include "gamestatus.h"
#include "attributestatus.h"
#include "typecountstatus.h"
#include "winlosecondition.h"
#include "attributewinlose.h"
#include "typecountwinlose.h"
using namespace std;

class GameEngine{
    Board board;
    NcursesView ncursesView;
    NcursesKeyInput keyInput;
public:
    GameEngine();
    void go();

    // Object adders
    int addBorder(const bool &spawner, BorderCollisionType borderType, const int &type,
                    const int &height, const int &despawnTickLimit, const bool &hidden);
    int addBitmapObject(const bool &spawner, const int &type, const int &height, const int &despawnTickLimit, 
                    const bool &hidden, const vector<tuple<int,int,char>> &triples);
    int addBasicObject(const bool &spawner, const int &type, const int &height, const int &despawnTickLimit, 
                    const bool &hidden, const int &row, const int &col, const char &symbol);
    int addRectangleObject(const bool &spawner, const int &type, const int &height, const int &despawnTickLimit, 
                    const bool &hidden, const int &topLeftRow, const int &topLeftCol, 
                    const int &length, const int &width, const char &symbol);

    // Movement adders
    void addWASDMovement(int id, int speed, bool holdDown);
    void addBorderMovement(int id, int speed, BorderType borderType);
    void addCyclicMovement(int id, int speed, const vector<vector<tuple<int,int,char>>> &cycles);
    void addStraightMovement(int id, int speed, int rowChange, int colChange);
    void addSpawnerMovement(int id, int speed, const vector<int> &spawnObjectIDs, bool spawnOnObject);

    // Collision adders
    void addStopCollision(int typeA, int typeB);
    void addOneWayDamageCollision(int typeA, int typeB, string health, string damage);
    void addBounceCollision(int typeA, int typeB);
    void addEndGameCollision(int typeA, int typeB, bool isWinCollision);
    void addSpawnerCollision(int typeA, int typeB, const vector<int> &spawnObjectIDs, bool spawnOnCollision);

    // Attribute adder
    void addAttribute(int id, string name, int value);

    // Win/Lose condition adders
    void addTypeCountWinLose(const bool &isWinCondition, const vector<pair<int,int>> &conditionPairs);
    void addAttributeWinLose(const bool &isWinCondition, const vector<tuple<int,int,string>> &conditionTuples);
    
    // Status line adders
    void addGameStatusLine();
    void addAttributeStatusLine(const int &id, const string &attributeName, const string &description);
    void addTypeCountStatusLine(const int &type, const string &description);

    ~GameEngine();
};
#endif
