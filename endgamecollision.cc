#include <iostream>
#include "endgamecollision.h"
using namespace std;

EndGameCollision::EndGameCollision(const bool &winCollision): Collision{}, winCollision{winCollision}{}
                                                                    
void EndGameCollision::handleCollision(Object *a, Object *b){}

bool EndGameCollision::isWinCollision(){return winCollision;}

EndGameCollision::~EndGameCollision(){}
