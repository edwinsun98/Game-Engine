#ifndef BORDEROBJECT_H
#define BORDEROBJECT_H
#include "object.h"
#include <vector>
#include <utility>
#include <map>
using namespace std;

class BorderObject: public Object{
    vector<tuple<int,int,char>> cells; // (row, column) coordinates that compose the border
    void savePosition() override;
public:
    BorderObject(const int &type, const int &height, const int &despawnTickLimit, const bool &hidden, 
                    const vector<Movement*> &movements, const map<string, int> &attributes);
    BorderObject(const BorderObject &other);
    void restorePosition() override;
    void draw() override;
    vector<pair<int,int>> getCollidablePoints() override;
    pair<int,int> getCenter() override;
    ~BorderObject() override;
};
#endif
