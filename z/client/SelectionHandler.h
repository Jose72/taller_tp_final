#ifndef CLIENT_SELECTIONHANDLER_H
#define CLIENT_SELECTIONHANDLER_H


#include <vector>
#include "Unit.h"
#include "Units_Protected.h"
#include "../common/Socket.h"
#include "Protocol.h"
#include "Camera2.h"

#define SELECTOR_D 20

class SelectionHandler {
private:
    bool unit_selected;
    Unit * unit;
    Protocol &protocol;
    int &id_client;
    Camera2 &cam;

public:
    SelectionHandler(Protocol &p, int &id, Camera2 &cam);
    void select_unit(std::vector<Unit*> &units);
    void set_target(int destX, int destY, Units_Protected &units);
    void set_location(int posX, int posY,Units_Protected &units);
    bool unit_select();

    Unit *getUnit();
};


#endif //CLIENT_SELECTIONHANDLER_H
