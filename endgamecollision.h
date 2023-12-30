#ifndef ENDGAMECOLLISION_H
#define ENDGAMECOLLISION_H
#include "collision.h"
#include "object.h"
using namespace std;

class EndGameCollision: public Collision{
    bool winCollision; // true if this collision leads to a win and false if it leads to a loss
public:
    EndGameCollision(const bool &winCollision);
    void handleCollision(Object *a, Object *b) override;
    bool isWinCollision();
    ~EndGameCollision() override;
};

#endif
