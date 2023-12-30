#ifndef NCURSESVIEW_H
#define NCURSESVIEW_H
#include "view.h"
using namespace std;

class NcursesView: public View{
public:
    NcursesView();
    void init() override;
    void notify(Subject *whofrom) override;
    ~NcursesView() override;
};

#endif
