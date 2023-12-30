#ifndef WASDMOVEMENT_H
#define WASDMOVEMENT_H
#include "movement.h"
using namespace std;

class WASDMovement: public Movement{
    bool holdDown;
    int rowChange = 0;
    int colChange = 0;
public:
    WASDMovement(int speed, bool holdDown); // holdDown is true if pressing the key
                                            // means holding it down until further notice
    WASDMovement(const WASDMovement &other);
    void updatePosition(Object *obj, const int &tickCount) override;
    bool reverseMovement() override;
    void setChange(const int &ch);
    ~WASDMovement() override;
};
#endif
