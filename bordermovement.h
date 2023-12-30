#ifndef BORDERMOVEMENT_H
#define BORDERMOVEMENT_H
#include "movement.h"
using namespace std;

enum class BorderType { TopEdge, RightEdge, DownEdge, LeftEdge};

class BorderMovement: public Movement{
    BorderType borderType;
    int rowChange = 0;
    int colChange = 0;
public:
    BorderMovement(int speed, BorderType borderType);
    BorderMovement(const BorderMovement &other);
    void updatePosition(Object *obj, const int &tickCount) override;
    bool reverseMovement() override;
    ~BorderMovement() override;
};

#endif
