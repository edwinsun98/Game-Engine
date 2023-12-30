#include <iostream>
#include <ncurses.h>
#include "basicobject.h"
using namespace std;

BasicObject::BasicObject(const int &type, const int &height, const int &despawnTickLimit, const bool &hidden, 
                            const vector<Movement*> &movements, const map<string, int> &attributes,
                            const int &row, const int &col, const char &symbol): 
                                        Object{type, height, despawnTickLimit, hidden, movements, attributes},
                                        row{row}, col{col}, symbol{symbol} {}

BasicObject::BasicObject(const BasicObject &other): Object{other}, row{other.row}, col{other.col},
                                                symbol{other.symbol}, prevRow{other.prevRow},
                                                prevCol{other.prevCol}, prevSymbol{other.prevSymbol}{}

void BasicObject::savePosition(){
    prevRow = row;
    prevCol = col;
    prevSymbol = symbol;
}

void BasicObject::restorePosition(){
    row = prevRow;
    col = prevCol;
    symbol = prevSymbol;
}

void BasicObject::draw(){
    string str{symbol};
    if(row >= 1 && row < 21 && col >= 1 && col < 79)
        mvprintw(row, col, str.c_str());
}

void BasicObject::setRow(const int &r){
    row = r;
}

void BasicObject::setCol(const int &c){
    col = c;
}

vector<pair<int,int>> BasicObject::getCollidablePoints(){
    vector<pair<int,int>> points;
    points.push_back(make_pair(row, col));
    return points;
}

int &BasicObject::getRow(){
    return row;
}

int &BasicObject::getCol(){
    return col;
}

char &BasicObject::getSymbol(){
    return symbol;
}

pair<int,int> BasicObject::getCenter(){
    return make_pair(row, col);
}

BasicObject::~BasicObject(){}
