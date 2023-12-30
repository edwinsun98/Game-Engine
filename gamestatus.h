#ifndef GAMESTATUS_H
#define GAMESTATUS_H
#include "statusline.h"
#include "board.h"
using namespace std;

class GameStatus: public StatusLine{
public:
    GameStatus();
    string getStatus(Board *board) override;
    ~GameStatus() override;
};

#endif
