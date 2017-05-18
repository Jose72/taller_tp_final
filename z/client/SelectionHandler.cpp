#include <iostream>
#include "SelectionHandler.h"

#define SIZE_OF_DELTA 20

#define BETWEEN(value, min, max) (((value) < (max)) && ((value) > (min)))

SelectionHandler::SelectionHandler(std::vector<Unit*> u):units(u){}

void SelectionHandler::select_unit(int posx, int posy) {
    int dx1 = posx - SIZE_OF_DELTA;
    int dx2 = posx + SIZE_OF_DELTA;
    int dy1 = posy - SIZE_OF_DELTA;
    int dy2 = posy + SIZE_OF_DELTA;

    for (int i = 0; i <this->units.size() ; ++i) {
        if(this->units[i]!= NULL){
            int posxd = units[i]->get_posx();
            std::cout <<posxd;
            if (BETWEEN(posxd, dx1, dx2)) {
                if (BETWEEN(units[i]->get_posy(), dy1, dy2)) {
                }
            }
        }
    }
}

