#include <iostream>
#include "straightmovement.h"
#include "basicobject.h"
#include "bitmapobject.h"
#include "rectangleobject.h"
using namespace std;

StraightMovement::StraightMovement(int speed, int rowChange, int colChange):
                                    Movement{speed}, rowChange{rowChange}, colChange{colChange} {}

StraightMovement::StraightMovement(const StraightMovement &other): Movement{other}, 
                                    rowChange{other.rowChange}, colChange{other.colChange} {}

void StraightMovement::updatePosition(Object *obj, const int &tickCount){
    if(tickCount%speed == 0){
        obj->setNetRowChange(obj->getNetRowChange() + rowChange);
        obj->setNetColChange(obj->getNetColChange() + colChange);

        // apply movement based on the type of the derived object class
        if(dynamic_cast<BasicObject*>(obj)){
            BasicObject *temp = dynamic_cast<BasicObject*>(obj);
            temp->getRow() += rowChange;
            temp->getCol() += colChange;
        }else if(dynamic_cast<BitmapObject*>(obj)){
            BitmapObject *temp = dynamic_cast<BitmapObject*>(obj);
            vector<tuple<int,int,char>> &triples = temp->getTriples();
            for(auto &t : triples){
                get<0>(t) += rowChange;
                get<1>(t) += colChange;
            }
        }else if(dynamic_cast<RectangleObject*>(obj)){
            RectangleObject *temp = dynamic_cast<RectangleObject*>(obj);
            vector<pair<int,int>> &cells = temp->getCells();
            for(auto &c : cells){
                c.first += rowChange;
                c.second += colChange;
            }
        }
    }
}

bool StraightMovement::reverseMovement(){
    rowChange *= -1;
    colChange *= -1;
    return 1;
}

StraightMovement::~StraightMovement(){}
