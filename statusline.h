#ifndef STATUSLINE_H
#define STATUSLINE_H
#include <string>
using namespace std;

class Board;

class StatusLine{
public:
    StatusLine();
    virtual string getStatus(Board *board) = 0;
    virtual ~StatusLine();
};

#endif
