#ifndef COLLIDABLE_H
#define COLLIDABLE_H
#include <vector>
#include <utility>
using namespace std;

class Collidable{
public:
    virtual vector<pair<int,int>> getCollidablePoints() = 0;
};

#endif
