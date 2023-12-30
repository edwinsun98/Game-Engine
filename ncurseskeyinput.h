#ifndef NCURSESKEYINPUT_H
#define NCURSESKEYINPUT_H
#include "controller.h"
using namespace std;

class NcursesKeyInput: public Controller{
    int buffer; // most recent char (expressed as int) taken as input
public:
    NcursesKeyInput();
    void takeInput() override;
    void addModel(Model *model) override;
    const int &getBuffer();
    ~NcursesKeyInput() override;
};

#endif
