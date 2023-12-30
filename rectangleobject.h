#ifndef RECTANGLEOBJECT_H
#define RECTANGLEOBJECT_H
#include "object.h"
#include <vector>
#include <map>
using namespace std;

class RectangleObject: public Object{
    int topLeftRow;
    int topLeftCol;
    int length;
    int width;
    char symbol;
    vector<pair<int,int>> cells; // (row, column) coordinates that compose the rectangle

    char prevSymbol;
    vector<pair<int,int>> prevCells;
    void savePosition() override;
public:
    RectangleObject(const int &type, const int &height, const int &despawnTickLimit, const bool &hidden, 
                    const vector<Movement*> &movements, const map<string, int> &attributes,
                    const int &topLeftRow, const int &topLeftCol, const int &length, 
                    const int &width, const char &symbol); // length (vertical) and width (horizontal)
    RectangleObject(const RectangleObject &other);
    void restorePosition() override;
    void draw() override;
    vector<pair<int,int>> getCollidablePoints() override;
    vector<pair<int,int>> &getCells();
    char &getSymbol();
    pair<int,int> getCenter() override;
    ~RectangleObject() override;
};
#endif
