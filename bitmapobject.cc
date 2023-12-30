#include <iostream>
#include <ncurses.h>
#include "bitmapobject.h"
using namespace std;


BitmapObject::BitmapObject(const int &type, const int &height, const int &despawnTickLimit, const bool &hidden, 
                            const vector<Movement*> &movements, const map<string, int> &attributes, 
                            const vector<tuple<int,int,char>> &triples):
                            Object{type, height, despawnTickLimit, hidden, movements, attributes}, triples{triples} {}

BitmapObject::BitmapObject(const BitmapObject &other): Object{other}, triples{other.triples},
                                                    prevTriples{other.prevTriples} {}

void BitmapObject::savePosition(){
    prevTriples = triples;
}

void BitmapObject::restorePosition(){
    triples = prevTriples;
}

void BitmapObject::draw(){
    for(auto &t : triples){
        if(get<0>(t) >= 1 && get<0>(t) < 21 && get<1>(t) >= 1 && get<1>(t) < 79){
            string str{get<2>(t)};
            mvprintw(get<0>(t), get<1>(t), str.c_str());
        }
    }
}

vector<pair<int,int>> BitmapObject::getCollidablePoints(){
    vector<pair<int,int>> points;
    for(auto &triple : triples){
        points.push_back(make_pair(get<0>(triple), get<1>(triple)));
    }
    return points;
}

vector<tuple<int,int,char>> &BitmapObject::getTriples(){
    return triples;
}

pair<int,int> BitmapObject::getCenter(){ // returns the average (center) of the points in this bitmap
    int rowSum = 0, colSum = 0;
    for(auto &i : triples){
        rowSum += get<0>(i);
        colSum += get<1>(i);
    }
    int size = (int)triples.size();
    return make_pair(rowSum/size, colSum/size);
}

BitmapObject::~BitmapObject(){}
