#ifndef MODEL_H
#define MODEL_H
#include "observer.h"
#include "subject.h"
#include "view.h"
using namespace std;

class Model: public Observer, public Subject{
public:
    Model();
    virtual void addView(View *view) = 0;
    virtual ~Model() = 0;
};

#endif
