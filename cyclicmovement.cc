#include <iostream>
#include "cyclicmovement.h"
#include "basicobject.h"
#include "bitmapobject.h"
#include "rectangleobject.h"
using namespace std;

CyclicMovement::CyclicMovement(int speed, vector<vector<tuple<int,int,char>>> forms): 
                                                    Movement{speed}, forms{forms}{}

CyclicMovement::CyclicMovement(const CyclicMovement &other): Movement{other}, forms{other.forms}{}

void CyclicMovement::updatePosition(Object *obj, const int &tickCount){
    if(tickCount%speed == 0){
        int netRowChange = obj->getNetRowChange();
        int netColChange = obj->getNetColChange();

        // apply the movement based on the type of the derived object class
        if(dynamic_cast<BasicObject*>(obj)){
            // check to make sure we are not accessing invalid indices
            if(cycleNumber < (int)forms.size() && forms[cycleNumber].size()){
                BasicObject *temp = dynamic_cast<BasicObject*>(obj);
                temp->getRow() = get<0>(forms[cycleNumber][0]) + netRowChange;
                temp->getCol() = get<1>(forms[cycleNumber][0]) + netColChange;
                temp->getSymbol() = get<2>(forms[cycleNumber][0]);
                cycleNumber = (cycleNumber+1)%((int)forms.size());
            }
        }else if(dynamic_cast<BitmapObject*>(obj)){
            // check to make sure we are not accessing invalid indices
            if(cycleNumber < (int)forms.size()){
                BitmapObject *temp = dynamic_cast<BitmapObject*>(obj);
                vector<tuple<int,int,char>> &triples = temp->getTriples();
                triples.clear();
                for(auto &triple : forms[cycleNumber]){
                    triples.push_back({get<0>(triple)+netRowChange, get<1>(triple)+netColChange,
                                        get<2>(triple)});
                }
                cycleNumber = (cycleNumber+1)%((int)forms.size());
            }
        }else if(dynamic_cast<RectangleObject*>(obj)){
            // check to make sure we are not accessing invalid indices
            if(cycleNumber < (int)forms.size() && forms[cycleNumber].size()){
                RectangleObject *temp = dynamic_cast<RectangleObject*>(obj);
                vector<pair<int,int>> &cells = temp->getCells();
                cells.clear();
                for(auto &triple : forms[cycleNumber]){
                    cells.push_back(make_pair(get<0>(triple)+netRowChange, get<1>(triple)+netColChange));
                }
                temp->getSymbol() = get<2>(forms[cycleNumber][0]);
                cycleNumber = (cycleNumber+1)%((int)forms.size()); 
            }
        }
    }
}

bool CyclicMovement::reverseMovement(){return 0;}

CyclicMovement::~CyclicMovement(){}
