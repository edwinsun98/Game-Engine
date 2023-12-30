#ifndef CLIENT_H
#define CLIENT_H
#include <vector>
#include <tuple>
#include <utility>
#include "gameengine.h"
using namespace std;

class Client{
    GameEngine eng; 
public:
    Client();
    void initializeSpaceInvaders();
    void initializeCoinCollectGame();
    void initializeTest();
    void go();
    ~Client();
};
#endif
