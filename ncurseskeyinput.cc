#include <iostream>
#include <ncurses.h>
#include "ncurseskeyinput.h"
using namespace std;

NcursesKeyInput::NcursesKeyInput(){}

void NcursesKeyInput::takeInput(){
    timeout(50);
    int input = -1;
    input = getch();
    if(input != -1){
        buffer = input;
        notifyObservers();
    }
}

void NcursesKeyInput::addModel(Model *model){
    attach(model);
}

const int &NcursesKeyInput::getBuffer(){
    return buffer;
}

NcursesKeyInput::~NcursesKeyInput(){}
