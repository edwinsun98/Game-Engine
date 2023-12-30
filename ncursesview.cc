#include <iostream>
#include <ncurses.h>
#include "ncursesview.h"
#include "board.h"
using namespace std;

NcursesView::NcursesView(){}

void NcursesView::init(){
    initscr();
    noecho();
}

void NcursesView::notify(Subject *whofrom){
    if(dynamic_cast<Board*>(whofrom)){
        refresh();
        clear();
        Board *temp = dynamic_cast<Board*>(whofrom);
        // update the Ncurses view
        temp->drawAll(); 
        temp->drawStatusLines();
        curs_set(0);
    }
}

NcursesView::~NcursesView(){
    endwin();
}
