#include <iostream>
#include <cassert>
#include <curses.h>
#include "board.h"
using namespace std;

Board::Board(const int &rows, const int &cols): rows{rows}, cols{cols}, theObjects{},
                                    spawnerObjects{}, spawnedObjectsQueue{},
                                    playerControlledMovements{}, collisionMap{}, 
                                    statusLines{}, winLoseConditions{} {}


BoardState Board::getBoardState() const{
    return state;
}

int Board::getAttribute(const int &id, const string &attributeName) const{
    for(auto &obj : theObjects){
        if(obj->getID() == id){
            return obj->getAttribute(attributeName);
        }
    }
    return 0;
}

int Board::countTypes(const int &type) const{
    int counter = 0;
    for(auto &obj : theObjects){
        if(obj->getType() == type){
            ++counter;
        }
    }
    return counter;
}

int Board::numWinLoseConditions() const{
    return (int)winLoseConditions.size();
}

void Board::addView(View *view){
    attach(view);
}

// Adds objects to the spawn queue based on the id numbers of the spawn objects
void Board::handleSpawn(const vector<int> &spawnIDs, const bool &isSpawnAtEvent, 
                        const int &startRow, const int &startCol){
    // isSpawnAtEvent is true if the new objects are spawned at the spawning object for movements or
    // if the new objects are spawned at the point of collision for colliisons
    for(auto &id : spawnIDs){
        for(auto &obj : spawnerObjects){
            if(obj->getID() == id){
                Object *object;
                if(dynamic_cast<BitmapObject*>(obj)){
                    object = new BitmapObject(*dynamic_cast<BitmapObject*>(obj));
                }else if(dynamic_cast<RectangleObject*>(obj)){
                    object = new RectangleObject(*dynamic_cast<RectangleObject*>(obj));
                }else if(dynamic_cast<BasicObject*>(obj)){
                    object = new BasicObject(*dynamic_cast<BasicObject*>(obj));
                    if(isSpawnAtEvent){
                        auto temp = dynamic_cast<BasicObject*>(object);
                        temp->setRow(startRow);
                        temp->setCol(startCol);
                    }
                }
                addToSpawnQueue(object);
                break;
            }
        }
    }
}

void Board::notify(Subject *whofrom){
    if(dynamic_cast<NcursesKeyInput*>(whofrom)){
        if(state != BoardState::Running)return;
        NcursesKeyInput *tempKeyInput = dynamic_cast<NcursesKeyInput*>(whofrom);
        for(auto &movement : playerControlledMovements){
            if(dynamic_cast<WASDMovement*>(movement)){
                dynamic_cast<WASDMovement*>(movement)->setChange(tempKeyInput->getBuffer());
            }
        }
    }else if(dynamic_cast<SpawnMovement*>(whofrom)){
        SpawnMovement *tempSpawnMovement = dynamic_cast<SpawnMovement*>(whofrom);
        handleSpawn(tempSpawnMovement->getSpawnObjectIDs(), tempSpawnMovement->isSpawnOnObject(), 
                    tempSpawnMovement->getStartRow(), tempSpawnMovement->getStartCol());
    }else if(dynamic_cast<SpawnerCollision*>(whofrom)){
        SpawnerCollision *tempSpawnCollision = dynamic_cast<SpawnerCollision*>(whofrom);
        handleSpawn(tempSpawnCollision->getSpawnObjectIDs(), tempSpawnCollision->isSpawnOnCollision(), 
                    tempSpawnCollision->getStartRow(), tempSpawnCollision->getStartCol());
    }
}

void Board::addSpawnedObjects(){ // adds any newly spawned objects from the queue to theObjects
    for(auto &obj : spawnedObjectsQueue){
        theObjects.push_back(obj);
    }
    spawnedObjectsQueue.clear();
}

void Board::processTick(const int &tickCount){
    if(state == BoardState::Running){
        handleMoves(tickCount);
        handleCollisions();
        handleWinLoseConditions();
        handleDespawn(); // check and update despawn tickcount and delete correspondingly (invisible off the screen)
        addSpawnedObjects(); // adds all spawn objects during this tick to theObjects
        notifyObservers();
    }
}

void Board::handleMoves(const int &tickCount){ // makes a move for all the objects in theObjects
    for(auto &object : theObjects){
        object->move(tickCount);
    }
}

// helper function for handleCollisions() that checks if these vectors have at least one pair in common
bool Board::intersect(vector<pair<int,int>> a, vector<pair<int,int>> b){
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    size_t aPtr = 0, bPtr = 0;
    for( ; aPtr < a.size() && bPtr < b.size(); ){
        int aValue = a[aPtr].first*cols+a[aPtr].second;
        int bValue = b[bPtr].first*cols+b[bPtr].second;
        if(aValue < bValue)++aPtr;
        else if(aValue > bValue)++bPtr;
        else return true;
    }
    return false;
}

// helper function that counts the number of pairs that are located on or outside of the border
size_t Board::countOutsideBorder(const vector<pair<int,int>> &points) const{
    size_t count = 0;
    for(const auto &point : points){
        if(!(point.first >= 1 && point.first < rows-1 && point.second >= 1 && point.second < cols-1)){
            ++count;
        }
    }
    return count;
}

void Board::processCollisionPairHelper(const int &aIndex, const int &bIndex){
    for(auto &x : collisionMap[theObjects[aIndex]->getType()]){
        if(x.first == theObjects[bIndex]->getType()){
            if(dynamic_cast<EndGameCollision*>(x.second) && state == BoardState::Running){
                state = ((dynamic_cast<EndGameCollision*>(x.second))->isWinCollision())
                            ? (BoardState::Won) : (BoardState::Lost);
            }else (x.second)->handleCollision(theObjects[aIndex], theObjects[bIndex]);
        }
    }
}

// processes the collisions between two objects (given their indices) within theObjects
void Board::processCollisionPair(const int &aIndex, const int &bIndex){
    processCollisionPairHelper(aIndex, bIndex);
    processCollisionPairHelper(bIndex, aIndex);
}

// handle all win/lose conditions specified by the client
void Board::handleWinLoseConditions(){
    for(auto &condition : winLoseConditions){
        if(state == BoardState::Running && condition->conditionsMet(this)){
            if(condition->getIsWinCondition()){
                state = BoardState::Won;
            }else state = BoardState::Lost;
        }
    }
}

void Board::handleBorderCollision(const vector<pair<int,int>> &objectPoints, 
                                const int &objectIndex, const int &borderIndex){
    if((theObjects[objectIndex]->isPlayerControlled() || 
        borderType == BorderCollisionType::Solid) && countOutsideBorder(objectPoints) > 0){
        // process all collisions associated with objects at index i and j
        processCollisionPair(objectIndex, borderIndex);
    }
}

// topmost method to handle collisions between all pairs of objects in theObjects
void Board::handleCollisions(){
    for(size_t i = 0; i < theObjects.size(); ++i){
        for(size_t j = i+1; j < theObjects.size(); ++j){
            vector<pair<int,int>> iPoints = theObjects[i]->getCollidablePoints();
            vector<pair<int,int>> jPoints = theObjects[j]->getCollidablePoints();
            if(iPoints.empty()){ // theObjects[i] is the border
                handleBorderCollision(jPoints, j, i);
            }else if(jPoints.empty()){ // the Objects[j] is the border
                handleBorderCollision(iPoints, i, j);
            }else if(intersect(iPoints, jPoints)){
                if(theObjects[i]->getHeight() > theObjects[j]->getHeight()){
                    theObjects[i]->setHidden(false);
                    theObjects[j]->setHidden(true);
                }else if(theObjects[j]->getHeight() > theObjects[i]->getHeight()){
                    theObjects[i]->setHidden(true);
                    theObjects[j]->setHidden(false);
                }else{
                    // process all collisions associated with objects at index i and j
                    processCollisionPair(i, j);
                }
            }
        }
    }
}

void Board::handleDespawn(){
    vector<size_t> toDespawn; // indexes of objects to despawn
    for(size_t i = 0; i < theObjects.size(); ++i){
        vector<pair<int,int>> points = theObjects[i]->getCollidablePoints();
        if(points.empty())continue; // borders do not despawn
        if(countOutsideBorder(points) == points.size()){
            if(++(theObjects[i]->getDespawnTickCount()) > theObjects[i]->getDespawnTickLimit()){
                toDespawn.push_back(i);
            }
        }else if(theObjects[i]->getForcedDespawn()){
            toDespawn.push_back(i);
        }else theObjects[i]->getDespawnTickCount() = 0;
    }
    
    // remove any objects that have gone off the board for over their specified time limit
    size_t offset = 0;
    for(size_t i = 0; i < toDespawn.size(); ++i){
        delete theObjects[toDespawn[i]-offset];
        theObjects.erase(theObjects.begin()+toDespawn[i]-offset);
        ++offset;
    }
}

void Board::drawAll(){
    for(size_t i = 0; i < theObjects.size(); ++i){
        if(!(theObjects[i]->isHidden()))theObjects[i]->draw();
        else theObjects[i]->setHidden(false);
    }
}

void Board::drawStatusLines(){
    int curRow = rows;
    for(auto &line : statusLines){
        string s = line->getStatus(this);
        mvprintw(curRow, 0, s.c_str());
        ++curRow;
    }
}

void Board::addObject(Object *object){
    theObjects.push_back(object);
}

void Board::addToSpawnQueue(Object *object){
    spawnedObjectsQueue.push_back(object);
}

void Board::addSpawnerObject(Object *object){
    spawnerObjects.push_back(object);
}

void Board::addControlledMovement(Movement *movement){
    playerControlledMovements.push_back(movement);
}

void Board::addMovementHelper(const int &id, Movement *movement, const bool &playerControlled,
                                vector<Object*> &vec){
    for(auto &obj : vec){
        if(obj->getID() == id){
            obj->addMovement(movement);
            if(playerControlled){
                obj->setPlayerControlled(true);
            }
        }
    }
}

void Board::addMovement(const int &id, Movement *movement, const bool &playerControlled){
    addMovementHelper(id, movement, playerControlled, theObjects);
    addMovementHelper(id, movement, playerControlled, spawnerObjects);
}

void Board::addCollision(const int &typeA, const int &typeB, Collision *collision){
    collisionMap[typeA].push_back(make_pair(typeB, collision));
}

// adds the specified attribute to the object with identifer id, which can
// be in theObjects or spawnerObjects
void Board::addAttribute(const int &id, const string &name, const int &value){
    for(auto &obj : theObjects){
        if(obj->getID() == id){
            obj->setAttribute(name, value);
            return;
        }
    }
    for(auto &obj : spawnerObjects){
        if(obj->getID() == id){
            obj->setAttribute(name, value);
            return;
        }
    }
}

void Board::setBorderType(BorderCollisionType type){
    borderType = type;
}

void Board::addStatusLine(StatusLine *line){
    statusLines.push_back(line);
}

void Board::addWinLoseCondition(WinLoseCondition *winLoseCondition){
    winLoseConditions.push_back(winLoseCondition);
}

Board::~Board(){
    for(auto &x : theObjects){
        delete x;
    }
    for(auto &x : spawnerObjects){
        delete x;
    }
    for(auto &x : spawnedObjectsQueue){
        delete x;
    }
    for(auto &x : collisionMap){
        for(auto &y : x.second){
            delete y.second;
        }
    }
    for(auto &x : statusLines){
        delete x;
    }
    for(auto &x : winLoseConditions){
        delete x;
    }
}
