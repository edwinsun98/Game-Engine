#include <iostream>
#include <ncurses.h>
#include "gameengine.h"

using namespace std;

const int ROWS = 22, COLUMNS = 80;

const int DEFAULT_TICK_LIMIT = 100000000; // default end game condition

const int ENDSCREEN_TICK_LIMIT = 100; // how many ticks the game stays on the endscreen

GameEngine::GameEngine():   board{ROWS, COLUMNS},
                            ncursesView{},
                            keyInput{} {
                                board.addView(&ncursesView);
                                keyInput.addModel(&board);
                            }

void GameEngine::go(){

    ncursesView.init();
    int tickCount = 0; // total number of ticks so far
    int endTickCount = 0; // number of ticks the endscreen has taken
    while(true){
        if(board.numWinLoseConditions() == 0 && tickCount > DEFAULT_TICK_LIMIT){ // default end game condition
            break;
        }
        if(board.getBoardState() != BoardState::Running){
            ++endTickCount;
            if(endTickCount >= ENDSCREEN_TICK_LIMIT){
                break;
            }
        }
        board.processTick(tickCount); // performs all operations needed for this tick
        keyInput.takeInput(); // take input from user
        ++tickCount;
    }
}

int GameEngine::addBorder(const bool &spawner, BorderCollisionType borderType, const int &type, const int &height, 
                            const int &despawnTickLimit, const bool &hidden){
    Object *object = new BorderObject(type, height, despawnTickLimit, hidden,
                                            vector<Movement*>{}, map<string,int>{});
    if(!spawner)board.addObject(object);
    else board.addSpawnerObject(object);
    board.setBorderType(borderType);
    return object->getID();
}

int GameEngine::addBitmapObject(const bool &spawner, const int &type, const int &height, const int &despawnTickLimit, 
                    const bool &hidden, const vector<tuple<int,int,char>> &triples){
    Object *object = new BitmapObject(type, height, despawnTickLimit, hidden, 
                            vector<Movement*>{}, map<string,int>{}, triples);
    if(!spawner)board.addObject(object);
    else board.addSpawnerObject(object);
    return object->getID();
}

int GameEngine::addBasicObject(const bool &spawner, const int &type, const int &height, const int &despawnTickLimit, 
                    const bool &hidden, const int &row, const int &col, const char &symbol){
    Object *object = new BasicObject(type, height, despawnTickLimit, hidden, 
                        vector<Movement*>{}, map<string,int>{}, row, col, symbol);
    if(!spawner)board.addObject(object);
    else board.addSpawnerObject(object);
    return object->getID();
}

int GameEngine::addRectangleObject(const bool &spawner, const int &type, const int &height, const int &despawnTickLimit, 
                    const bool &hidden, const int &topLeftRow, const int &topLeftCol, 
                    const int &length, const int &width, const char &symbol){
    Object *object = new RectangleObject(type, height, despawnTickLimit, hidden, vector<Movement*>{},
                        map<string,int>{}, topLeftRow, topLeftCol, length, width, symbol);
    if(!spawner)board.addObject(object);
    else board.addSpawnerObject(object);
    return object->getID();
}

void GameEngine::addWASDMovement(int id, int speed, bool holdDown){
    Movement *movement = new WASDMovement(speed, holdDown);
    board.addControlledMovement(movement);
    board.addMovement(id, movement, 1);
}

void GameEngine::addBorderMovement(int id, int speed, BorderType borderType){
    Movement *movement = new BorderMovement(speed, borderType);
    board.addMovement(id, movement, 0);
}

void GameEngine::addCyclicMovement(int id, int speed, const vector<vector<tuple<int,int,char>>> &cycles){
    Movement *movement = new CyclicMovement(speed, cycles);
    board.addMovement(id, movement, 0);
}

void GameEngine::addStraightMovement(int id, int speed, int rowChange, int colChange){
    Movement *movement = new StraightMovement(speed, rowChange, colChange);
    board.addMovement(id, movement, 0);
}

void GameEngine::addSpawnerMovement(int id, int speed, const vector<int> &spawnObjectIDs,
                                    bool spawnOnObject){
    Movement *movement = new SpawnMovement(speed, spawnObjectIDs, &board, spawnOnObject);
    board.addMovement(id, movement, 0);
}

void GameEngine::addStopCollision(int typeA, int typeB){
    if(typeA > typeB)swap(typeA, typeB);
    Collision *collision = new StopCollision();
    board.addCollision(typeA, typeB, collision);
}

// Object of type typeA damages object of type typeB during collision
// Object of typeA must have attribute damage and object of typeB must have attribute health
void GameEngine::addOneWayDamageCollision(int typeA, int typeB, string health, string damage){
    Collision *collision = new OneWayDamage(health, damage);
    board.addCollision(typeA, typeB, collision);
}

void GameEngine::addBounceCollision(int typeA, int typeB){
    Collision *collision = new BounceOffCollision();
    board.addCollision(typeA, typeB, collision);
}

void GameEngine::addEndGameCollision(int typeA, int typeB, bool isWinCollision){
    Collision *collision = new EndGameCollision(isWinCollision);
    board.addCollision(typeA, typeB, collision);
}

void GameEngine::addSpawnerCollision(int typeA, int typeB, const vector<int> &spawnObjectIDs, 
                                        bool spawnOnCollision){
    Collision *collision = new SpawnerCollision(spawnObjectIDs, &board, spawnOnCollision);
    board.addCollision(typeA, typeB, collision);
}

void GameEngine::addAttribute(int id, string name, int value){
    board.addAttribute(id, name, value);
}

void GameEngine::addGameStatusLine(){
    StatusLine *line = new GameStatus();
    board.addStatusLine(line);
}

void GameEngine::addAttributeStatusLine(const int &id, const string &attributeName, 
                                        const string &description){
    StatusLine *line = new AttributeStatus(id, attributeName, description);
    board.addStatusLine(line);
}

void GameEngine::addTypeCountStatusLine(const int &type, const string &description){
    StatusLine *line = new TypeCountStatus(type, description);
    board.addStatusLine(line);
}

void GameEngine::addTypeCountWinLose(const bool &isWinCondition, const vector<pair<int,int>> &conditionPairs){
    WinLoseCondition *condition = new TypeCountWinLose(isWinCondition, conditionPairs);
    board.addWinLoseCondition(condition);
}

void GameEngine::addAttributeWinLose(const bool &isWinCondition, const vector<tuple<int,int,string>> &conditionTuples){
    WinLoseCondition *condition = new AttributeWinLose(isWinCondition, conditionTuples);
    board.addWinLoseCondition(condition);
}

GameEngine::~GameEngine(){

}
