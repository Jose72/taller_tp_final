#include <iostream>
#include "SelectionHandler.h"
#include "Units_Protected.h"

#define SIZE_OF_DELTA 16

#define BETWEEN(value, min, max) (((value) < (max)) && ((value) > (min)))

SelectionHandler::SelectionHandler(Protocol &p, int &id, Camera2 &cam):protocol(p),
                                                                       id_client(id),
                                                                       cam(cam),
                                                                       unit_selected(false),
                                                                       unit(nullptr){

}

void SelectionHandler::set_location(int posX, int posY,Units_Protected &units) {
    int dx1 = posX - SIZE_OF_DELTA;
    int dx2 = posX + SIZE_OF_DELTA;
    int dy1 = posY - SIZE_OF_DELTA;
    int dy2 = posY + SIZE_OF_DELTA;
    unit = units.selectUnit(posX,posY,unit_selected, id_client);
}

void SelectionHandler::selectUnits(int startX, int endX, int startY, int endY, Units_Protected &units) {
    int rangeX1;
    int rangeX2;
    int rangeY1;
    int rangeY2;
    if(startX<= endX){
        rangeX1 = startX;
        rangeX2 = endX;
    } else{
        rangeX1 = endX;
        rangeX2 = startX;
    }
    if(startY <= endY){
        rangeY1 = startY;
        rangeY2 = endY;
    } else{
        rangeY1 = endY;
        rangeY2 = startY;
    }

    this->unitsSelected = units.selectUnits(rangeX1,rangeX2,rangeY1,rangeY2,unit_selected,id_client);

}

Unit* SelectionHandler::getUnit(){
    return this->unit;
}

bool SelectionHandler::unit_select() {
    return this->unit_selected;
}

void SelectionHandler::set_target(int destX, int destY, Units_Protected &units) {
    Action action;
    Unit * enemy;

    if(unit_selected) {
        enemy = units.selectEnemy(destX,destY,action, id_client);
        switch (action){
            case MOVE:
                for (int i = 0; i <this->unitsSelected.size() ; ++i) {
                    protocol.moveUnitCS(this->unitsSelected[i]->get_unit_code(),destX,destY);
                }
                break;
            case ATTACK:
                if((enemy->get_state() != DEAD2) && (enemy->get_state() != DEAD1)) {
                    for (int i = 0; i <this->unitsSelected.size() ; ++i) {
                        protocol.attackUnitCS(this->unitsSelected[i]->get_unit_code(), enemy->get_unit_code());
                    }
                }
                break;
            case DRIVE:
                bool finded = false;
                Unit *driver = getDriver(finded);
                if(finded){
                    protocol.driveUnitCS(driver->get_unit_code(),enemy->get_unit_code());
                    unit_selected = false;
                }
                break;
        }

    }
}

Unit* SelectionHandler::getDriver(bool &finded) {
    for (int i = 0; i <this->unitsSelected.size() ; ++i) {
        FlagsUnitType type = this->unitsSelected[i]->get_type();
        if((type!=FACTORY_ROBOTS_ALIVE) &&
           (type != FACTORY_VEHICLES_ALIVE) &&
                (type != FORT_ALIVE)){
            finded = true;
            return this->unitsSelected[i];
        }
    }
    return nullptr;
}



