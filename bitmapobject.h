#ifndef BITMAPOBJECT_H
#define BITMAPOBJECT_H
#include <vector>
#include <map>
#include <tuple>
#include "object.h"
using namespace std;

class BitmapObject: public Object{
    vector<tuple<int,int,char>> triples;
    vector<tuple<int,int,char>> prevTriples; // stores the triples vector prior to the most recent series of moves
    void savePosition() override;
public:
    BitmapObject(const int &type, const int &height, const int &despawnTickLimit, const bool &hidden, 
                    const vector<Movement*> &movements, const map<string, int> &attributes, 
                    const vector<tuple<int,int,char>> &triples);
    BitmapObject(const BitmapObject &other);
    void restorePosition() override;
    void draw() override;
    vector<pair<int,int>> getCollidablePoints() override;
    vector<tuple<int,int,char>> &getTriples();
    pair<int,int> getCenter() override;
    ~BitmapObject() override;
};
#endif
