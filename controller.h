#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "subject.h"
#include "model.h"
using namespace std;

class Controller: public Subject{
public:
    Controller();
    virtual void takeInput() = 0;
    virtual void addModel(Model *model) = 0;
    virtual ~Controller() = 0;
};

#endif
