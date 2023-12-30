#ifndef VIEW_H
#define VIEW_H
#include "observer.h"
using namespace std;

class View: public Observer{
public:
    View();
    virtual void init() = 0;
    virtual ~View() = 0;
};

#endif
