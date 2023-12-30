#include <iostream>
#include <ncurses.h>
#include "borderobject.h"
using namespace std;

BorderObject::BorderObject(const int &type, const int &height, const int &despawnTickLimit, const bool &hidden, 
                                    const vector<Movement*> &movements, const map<string, int> &attributes):
                                    Object{type, height, despawnTickLimit, hidden, movements, attributes}{
    for(int j = 1; j < 79; j++)cells.push_back({0, j, '-'});
    for(int j = 1; j < 79; j++)cells.push_back({21, j, '-'});
    for(int i = 0; i < 22; i++)cells.push_back({i, 0, ((i == 0 || i == 21) ? '+' : '|')});
    for(int i = 0; i < 22; i++)cells.push_back({i, 79, ((i == 0 || i == 21) ? '+' : '|')});
}

BorderObject::BorderObject(const BorderObject &other): Object{other}, cells{other.cells} {}

// Border's positions are fixed
void BorderObject::savePosition(){}

void BorderObject::restorePosition(){}

void BorderObject::draw(){
    for(auto &t : cells){
        string str{get<2>(t)};
        mvprintw(get<0>(t), get<1>(t), str.c_str());
    }
}

vector<pair<int,int>> BorderObject::getCollidablePoints(){
    vector<pair<int,int>> points;
    return points;
}

pair<int,int> BorderObject::getCenter(){
    return make_pair(0, 0);
}

BorderObject::~BorderObject(){}
