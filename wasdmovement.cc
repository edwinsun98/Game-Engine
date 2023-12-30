#include <iostream>
#include "wasdmovement.h"
#include "basicobject.h"
#include "bitmapobject.h"
#include "rectangleobject.h"
using namespace std;

WASDMovement::WASDMovement(int speed, bool holdDown): Movement{speed}, holdDown{holdDown} {}

WASDMovement::WASDMovement(const WASDMovement &other): Movement{other}, holdDown{other.holdDown}{
    rowChange = other.rowChange;
    colChange = other.colChange;
}

void WASDMovement::updatePosition(Object *obj, const int &tickCount){
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
        }else return;
        if(!holdDown){
            rowChange = 0;
            colChange = 0;
        }
    }
}

bool WASDMovement::reverseMovement(){return 0;}

void WASDMovement::setChange(const int &ch){
    if(ch == (int)'w'){
        rowChange = -1;
        colChange = 0;
    }else if(ch == (int)'a'){
        rowChange = 0;
        colChange = -1;
    }else if(ch == (int)'s'){
        rowChange = 1;
        colChange = 0;
    }else if(ch == (int)'d'){
        rowChange = 0;
        colChange = 1;
    }
}

WASDMovement::~WASDMovement(){}
