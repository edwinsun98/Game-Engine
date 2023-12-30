#ifndef BASICOBJECT_H
#define BASICOBJECT_H
#include "object.h"
#include <vector>
#include <utility>
#include <map>
using namespace std;

class BasicObject: public Object{
    int row;
    int col;
    char symbol;

    int prevRow;
    int prevCol;
    char prevSymbol;
    void savePosition() override;
public:
    BasicObject(const int &type, const int &height, const int &despawnTickLimit, const bool &hidden, 
                    const vector<Movement*> &movements, const map<string, int> &attributes,
                    const int &row, const int &col, const char &symbol);
    BasicObject(const BasicObject &other);
    void restorePosition() override;
    void draw() override;
    void setRow(const int &r);
    void setCol(const int &c);
    vector<pair<int,int>> getCollidablePoints() override;
    int &getRow();
    int &getCol();
    char &getSymbol();
    pair<int,int> getCenter() override;
    ~BasicObject() override;
};
#endif
