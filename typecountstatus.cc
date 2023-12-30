#include <iostream>
#include "typecountstatus.h"
using namespace std;

TypeCountStatus::TypeCountStatus(const int &type, const string &description): 
                        StatusLine{}, type{type}, description{description}{}

string TypeCountStatus::getStatus(Board *board){
    string res = description;
    res += to_string(board->countTypes(type));
    return res;
}

TypeCountStatus::~TypeCountStatus(){}
