#ifndef CLIENT_SELECTIONHANDLER_H
#define CLIENT_SELECTIONHANDLER_H


#include <vector>
#include "Unit.h"
#include "Units_Protected.h"

#define SELECTOR_D 20

class SelectionHandler {
private:
    int destinyX;
    int destinyY;
    bool unit_selected;
    Unit * unit;


public:
    SelectionHandler();
    void select_unit(std::vector<Unit*> &units);
    void set_destiny(int destX, int destY);
    void set_location(int posX, int posY,Units_Protected &units);
    void move_unit();
    bool unit_select();
};


#endif //CLIENT_SELECTIONHANDLER_H
