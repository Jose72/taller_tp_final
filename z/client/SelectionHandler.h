#ifndef CLIENT_SELECTIONHANDLER_H
#define CLIENT_SELECTIONHANDLER_H


#include <vector>
#include "Unit.h"
#include "Grunt.h"

class SelectionHandler {
private:
    std::vector<Unit*> & units;
    Grunt * unit_s;


public:
    SelectionHandler(std::vector<Unit *> u);
    void select_unit(int posx, int posy);
    Grunt* get_unit_s();
};


#endif //CLIENT_SELECTIONHANDLER_H
