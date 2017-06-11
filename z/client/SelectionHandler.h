#ifndef CLIENT_SELECTIONHANDLER_H
#define CLIENT_SELECTIONHANDLER_H


#include <vector>
#include "Unit.h"
#include "Units_Protected.h"
#include "../common/Socket.h"
#include "Protocol.h"

#define SELECTOR_D 20

class SelectionHandler {
private:
    int destinyX;
    int destinyY;
    bool unit_selected;
    Unit * unit;
    Protocol &protocol;
    int &id_client;

public:
    SelectionHandler(Protocol &p, int &id);
    void select_unit(std::vector<Unit*> &units);
    void set_objetive(int destX, int destY, Units_Protected &units);
    void set_location(int posX, int posY,Units_Protected &units);
    void move_unit();
    bool unit_select();

    Unit *getUnit();
};


#endif //CLIENT_SELECTIONHANDLER_H
