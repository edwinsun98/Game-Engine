#include <iostream>
#include "bordermovement.h"
#include "basicobject.h"
#include "bitmapobject.h"
#include "rectangleobject.h"
using namespace std;

BorderMovement::BorderMovement(int speed, BorderType borderType): Movement{speed}, borderType{borderType} {
    if(borderType == BorderType::DownEdge){
        rowChange = 1;
    }else if(borderType == BorderType::LeftEdge){
        colChange = -1;
    }else if(borderType == BorderType::TopEdge){
        rowChange = -1;
    }else if(borderType == BorderType::RightEdge){
        colChange = 1;
    }
}

BorderMovement::BorderMovement(const BorderMovement &other): Movement{other}, 
                                                            borderType{other.borderType}{
    rowChange = other.rowChange;
    colChange = other.colChange;
}


void BorderMovement::updatePosition(Object *obj, const int &tickCount){
    if(tickCount%speed == 0){
        obj->setNetRowChange(obj->getNetRowChange() + rowChange);
        obj->setNetColChange(obj->getNetColChange() + colChange);

        // apply movement based on the derived type of the object
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

bool BorderMovement::reverseMovement(){
    if(borderType == BorderType::DownEdge){
        borderType = BorderType::TopEdge;
        rowChange *= -1;
    }else if(borderType == BorderType::LeftEdge){
        borderType = BorderType::RightEdge;
        colChange *= -1;
    }else if(borderType == BorderType::TopEdge){
        borderType = BorderType::DownEdge;
        rowChange *= -1;
    }else if(borderType == BorderType::RightEdge){
        borderType = BorderType::LeftEdge;
        colChange *= -1;
    }
    return 1;
}

BorderMovement::~BorderMovement(){}
