#ifndef CLIENT_SELECTIONHANDLER_H
#define CLIENT_SELECTIONHANDLER_H


#include <vector>
#include "Unit.h"


class SelectionHandler {
private:
    std::vector<Unit*> & units;

public:
    SelectionHandler(std::vector<Unit *> u);
    void select_unit(int posx, int posy);
};


#endif //CLIENT_SELECTIONHANDLER_H
