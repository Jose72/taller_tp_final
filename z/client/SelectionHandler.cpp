#include <iostream>
#include "SelectionHandler.h"
#include "Units_Protected.h"

#define SIZE_OF_DELTA 20

#define BETWEEN(value, min, max) (((value) < (max)) && ((value) > (min)))

SelectionHandler::SelectionHandler(Protocol &p):protocol(p){
    this->unit_selected = false;
}

void SelectionHandler::set_location(int posX, int posY,Units_Protected &units) {
    int dx1 = posX - SIZE_OF_DELTA;
    int dx2 = posX + SIZE_OF_DELTA;
    int dy1 = posY - SIZE_OF_DELTA;
    int dy2 = posY + SIZE_OF_DELTA;
    unit = units.selectUnit(dx1,dx2,dy1,dy2,unit_selected);

}

Unit* SelectionHandler::getUnit(){
    return this->unit;
}

void SelectionHandler::move_unit() {
    if(unit_selected){
        int unit_posX = this->unit->get_posx();
        int unit_posY = this->unit->get_posy();
        Uint32 ticks =  SDL_GetTicks();
       // if ((ticks % 10) == 0) {
            if (unit_posX < this->destinyX) {
                unit_posX += 1;
            }
            if (unit_posX > this->destinyX) {
                unit_posX -= 1;
            }
            if (unit_posY < this->destinyY) {
                unit_posY += 1;
            }
            if (unit_posY > this->destinyY) {
                unit_posY -= 1;
            }
      //  }
        this->unit->set_pos(unit_posX,unit_posY);
    }
}
bool SelectionHandler::unit_select() {
    return this->unit_selected;
}

void SelectionHandler::set_objetive(int destX, int destY, Units_Protected &units) {
    int dx1 = destX - SIZE_OF_DELTA;
    int dx2 = destX + SIZE_OF_DELTA;
    int dy1 = destY - SIZE_OF_DELTA;
    int dy2 = destY + SIZE_OF_DELTA;
    bool attack = false;
    Unit * enemy;

    if(unit_selected) {
        enemy = units.selectUnit(dx1,dx2,dy1,dy2,attack);
            if (attack) {
                if((enemy->get_state() != DEAD2) && (enemy->get_state() != DEAD1)) {
                    protocol.attackUnitCS(unit->get_unit_code(), enemy->get_unit_code());
                }
            } else {
                protocol.moveUnitCS(unit->get_unit_code(), destX, destY);
            }
    }
}



