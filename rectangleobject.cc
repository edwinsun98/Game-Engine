#include <iostream>
#include <ncurses.h>
#include "rectangleobject.h"
using namespace std;

RectangleObject::RectangleObject(const int &type, const int &height, const int &despawnTickLimit, const bool &hidden, 
                                    const vector<Movement*> &movements, const map<string, int> &attributes,
                                    const int &topLeftRow, const int &topLeftCol, const int &length, 
                                    const int &width, const char &symbol):
                                    Object{type, height, despawnTickLimit, hidden, movements, attributes},
                                    topLeftRow{topLeftRow}, topLeftCol{topLeftCol}, length{length},
                                    width{width}, symbol{symbol}{
                                        for(int i = topLeftRow; i < topLeftRow+length; ++i){
                                            for(int j = topLeftCol; j < topLeftCol+width; ++j){
                                                cells.push_back(make_pair(i, j));
                                            }
                                        }
                                    }

RectangleObject::RectangleObject(const RectangleObject &other): 
                                    Object{other}, topLeftRow{other.topLeftRow}, 
                                    topLeftCol{other.topLeftCol}, length{other.length},
                                    width{other.width}, symbol{other.symbol}, cells{other.cells},
                                    prevSymbol{other.prevSymbol}, prevCells{other.prevCells} {}

void RectangleObject::savePosition(){
    prevSymbol = symbol;
    prevCells = cells;
}

void RectangleObject::restorePosition(){
    symbol = prevSymbol;
    cells = prevCells;
}

void RectangleObject::draw(){
    string str{symbol};
    for(auto &t : cells){
        mvprintw(t.first, t.second, str.c_str());
    }
}

vector<pair<int,int>> RectangleObject::getCollidablePoints(){
    return cells;
}

vector<pair<int,int>> &RectangleObject::getCells(){
    return cells;
}

char &RectangleObject::getSymbol(){
    return symbol;
}

pair<int,int> RectangleObject::getCenter(){
    return make_pair(topLeftRow+length/2, topLeftCol+width/2);
}

RectangleObject::~RectangleObject(){}
