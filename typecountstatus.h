#ifndef TYPECOUNTSTATUS_H
#define TYPECOUNTSTATUS_H
#include "statusline.h"
#include "board.h"
using namespace std;

// this class is used to output the count of a specified type of objects to the status bar
class TypeCountStatus: public StatusLine{
    int type;
    string description;
public:
    TypeCountStatus(const int &type, const string &description);
    string getStatus(Board *board) override;
    ~TypeCountStatus() override;
};

#endif
