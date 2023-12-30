#include <iostream>
#include "object.h"
using namespace std;

Object::Object(const int &type, const int &height, const int &despawnTickLimit, const bool &hidden, 
            const vector<Movement*> &movements, const map<string, int> &attributes):
            type{type}, height{height}, despawnTickLimit{despawnTickLimit}, hidden{hidden}, 
            movements{movements}, attributes{attributes} {
    id = id_counter++;
}

Object::Object(const Object &other): type{other.type}, height{other.height},
                                    despawnTickLimit{other.despawnTickLimit}, hidden{other.hidden},
                                    movements{}, attributes{other.attributes}{
    playerControlled = other.playerControlled;
    forcedDespawn = other.forcedDespawn;
    despawnTickCount = other.despawnTickCount;
    for(auto &movement : other.movements){
        Movement *newMovement;
        if(dynamic_cast<StraightMovement*>(movement)){
            newMovement = new StraightMovement(*dynamic_cast<StraightMovement*>(movement));
        }else if(dynamic_cast<CyclicMovement*>(movement)){
            newMovement = new CyclicMovement(*dynamic_cast<CyclicMovement*>(movement));
        }else if(dynamic_cast<WASDMovement*>(movement)){
            newMovement = new WASDMovement(*dynamic_cast<WASDMovement*>(movement));
        }else if(dynamic_cast<BorderMovement*>(movement)){
            newMovement = new BorderMovement(*dynamic_cast<BorderMovement*>(movement));
        }
        movements.push_back(newMovement);
    }
    id = id_counter++;
}

void Object::setNetRowChange(const int &x){
    netRowChange = x;
}

void Object::setNetColChange(const int &x){
    netColChange = x;
}

void Object::move(const int &tickCount){
    savePosition();
    for(auto &move : movements){
        move->updatePosition(this, tickCount);
    }
}

void Object::reverseMovements(){ // make one step in the opposite (newly updated)
                                 // direction after reversing movement
    for(auto &move : movements){
        if(move->reverseMovement()){
            move->updatePosition(this, 0);
        }
    }
}

void Object::addMovement(Movement *movement){
    movements.push_back(movement);
}

void Object::setForcedDespawn(const bool &despawn){
    forcedDespawn = despawn;
}

void Object::setHidden(const bool &hid){
    hidden = hid;
}

void Object::setPlayerControlled(const bool &controlled){
    playerControlled = controlled;
}

void Object::setAttribute(const string &name, const int &val){
    attributes[name] = val;
}

const int &Object::getAttribute(const string &name){
    return attributes[name];
}

const bool &Object::getForcedDespawn(){return forcedDespawn;}

const bool &Object::isHidden(){return hidden;}

const bool &Object::isPlayerControlled(){return playerControlled;}

int &Object::getDespawnTickCount(){return despawnTickCount;}

const int &Object::getDespawnTickLimit(){return despawnTickLimit;}

const int &Object::getID(){return id;}

const int &Object::getHeight(){return height;}

const int &Object::getType(){return type;}

const int &Object::getNetRowChange(){return netRowChange;}

const int &Object::getNetColChange(){return netColChange;}

Object::~Object(){
    for(auto &x : movements){
        delete x;
    }
}
