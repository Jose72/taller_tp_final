#include <iostream>
#include "SelectionHandler.h"
#include "Units_Protected.h"

#define SIZE_OF_DELTA 20

#define BETWEEN(value, min, max) (((value) < (max)) && ((value) > (min)))

SelectionHandler::SelectionHandler(tSocket &s):socket(s){
    this->unit_selected = false;
}

void SelectionHandler::set_location(int posX, int posY,Units_Protected &units) {
    int dx1 = posX - SIZE_OF_DELTA;
    int dx2 = posX + SIZE_OF_DELTA;
    int dy1 = posY - SIZE_OF_DELTA;
    int dy2 = posY + SIZE_OF_DELTA;

    for (int i = 0; i<units.size() ; ++i) {
        if(BETWEEN(units[i]->get_posx(),dx1,dx2)){
            if(BETWEEN(units[i]->get_posy(),dy1,dy2)){
                this->unit_selected = true;
                this->unit = units[i];
                set_destiny(this->unit->get_posx(),this->unit->get_posy());
            }
        }
    }
}

void SelectionHandler::move_unit() {
    if(unit_selected){
        int unit_posX = this->unit->get_posx();
        int unit_posY = this->unit->get_posy();
        Uint32 ticks =  SDL_GetTicks();
        if ((ticks % 10) == 0) {
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
        }
        this->unit->set_pos(unit_posX,unit_posY);
    }
}
bool SelectionHandler::unit_select() {
    return this->unit_selected;
}

void SelectionHandler::set_destiny(int destX, int destY) {
    this->destinyX = destX;
    this->destinyY = destY;
    //int unit_id = this->unit->get_id();
    //socket.send((char*)id,4);
    socket.send((char*)destX,4);
    socket.send((char*)destY,4);

}



