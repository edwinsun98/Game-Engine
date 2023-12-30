#ifndef ATTRIBUTESTATUS_H
#define ATTRIBUTESTATUS_H
#include "statusline.h"
#include "board.h"
using namespace std;

class AttributeStatus: public StatusLine{
    int id;
    string attributeName;
    string description;
public:
    AttributeStatus(const int &id, const string &attributeName, const string &description);
    string getStatus(Board *board) override;
    ~AttributeStatus() override;
};
#endif
