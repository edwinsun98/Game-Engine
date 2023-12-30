#include <iostream>
#include "attributestatus.h"
using namespace std;

AttributeStatus::AttributeStatus(const int &id, const string &attributeName, const string &description): 
                        StatusLine{}, id{id}, attributeName{attributeName}, description{description}{}

string AttributeStatus::getStatus(Board *board){
    string res = description;
    res += to_string(board->getAttribute(id, attributeName));
    return res;
}

AttributeStatus::~AttributeStatus(){}
