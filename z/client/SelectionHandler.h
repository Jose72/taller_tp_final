#ifndef CLIENT_SELECTIONHANDLER_H
#define CLIENT_SELECTIONHANDLER_H


#include <vector>
#include "Unit.h"

#define SELECTOR_D 20

class SelectionHandler {
private:
    int posX;
    int posY;


public:
    SelectionHandler(std::vector<Unit *> u);
    void select_unit(int posx, int posy);
};


#endif //CLIENT_SELECTIONHANDLER_H
