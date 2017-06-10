#include "Units_Protected.h"
#include "../common/Lock.h"

#define OWNER_BLUE 1
#define OWNER_GREEN 2
#define OWNER_RED 3
#define OWNER_YELLOW 4

#define BETWEEN(value, min, max) (((value) < (max)) && ((value) > (min)))

Units_Protected::Units_Protected(std::map<int, Unit*> &um): units_map(um){}

Units_Protected::~Units_Protected() {}

void Units_Protected::add(int cod_u, Unit *unit) {
    tLock(this->mut);
    units_map[cod_u]= unit;
}

Unit* Units_Protected::operator[](int i) {
    tLock(this->mut);
    return units_map[i];
}

int Units_Protected::size() {
    tLock(this->mut);
    return units_map.size();
}

void Units_Protected::animate(int limitXL, int limitXR, int limitYU, int limitYD , SDL_Rect cameraRect) {
    tLock(this->mut);
    std::map<int, Unit*>::iterator it;
    for (it = units_map.begin();it != units_map.end() ; ++it) {
        if (BETWEEN(it->second->get_posx(), limitXL, limitXR)) {
            if (BETWEEN(it->second->get_posy(), limitYU, limitYD)) {
                it->second->animate(cameraRect);
            }
        }
    }
}

Unit* Units_Protected::selectUnit(int dx1, int dx2, int dy1, int dy2, bool &found) {
    tLock(this->mut);
    Unit *unitSelected;
    found = false;
    std::map<int, Unit*>::iterator it;
    for (it = units_map.begin();it != units_map.end() ; ++it) {
        if (BETWEEN(it->second->get_posx(), dx1, dx2)) {
            if (BETWEEN(it->second->get_posy(), dy1, dy2)) {
                unitSelected = it->second;
                found = true;
            }
        }
    }
    return unitSelected;
}

void Units_Protected::cleanDeadUnits() {
    tLock(this->mut);
    std::map<int, Unit*>::iterator it;
    for (it = units_map.begin();it != units_map.end() ; ++it) {
        if (it->second->get_cameraPosX() == DEAD2){
            units_map.erase(it->first);
        }
    }

}

enum units {
    GRUNT = 0, PSYCHO = 1, TOUGHT = 2, PYRO = 3, SNIPER = 4, LAZER = 5,
    JEEP = 6, MEDIUM_TANK = 7, LIGHT_TANK = 8, HEAVY_TANK = 9, MML = 10,
    FORT = 11, ROBOT_FACTORY = 12, VEHICLE_FACTORY = 13,
    FLAG = 14,
    LLAMAS = 15, HCP = 16, LASER = 17, MISIL = 18, BALAS = 19};

void Units_Protected::createIsNotExist(int cod_unit, int unit_type, int unit_owner, int posX, int posY, Factory_Units &factory) {
    tLock(this->mut);
    if(units_map.find(cod_unit) == units_map.end()){
        switch (unit_type){
            case GRUNT:
                createUnit(cod_unit,unit_owner,posX,posY,factory,
                           BLUE_GRUNT,GREEN_GRUNT,RED_GRUNT,YELLOW_GRUNT);
                break;
            case PSYCHO:
                createUnit(cod_unit,unit_owner,posX,posY,factory,
                           BLUE_PSYCHO,GREEN_PSYCHO,RED_PSYCHO,YELLOW_PSYCHO);
                break;
            case TOUGHT:
                createUnit(cod_unit,unit_owner,posX,posY,factory,
                           BLUE_TOUGHT,GREEN_TOUGHT,RED_TOUGHT,YELLOW_TOUGHT);
                break;
            case PYRO:
                createUnit(cod_unit,unit_owner,posX,posY,factory,
                           BLUE_PYRO,GREEN_PYRO,RED_PYRO,YELLOW_PYRO);
                break;
            case SNIPER:
                createUnit(cod_unit,unit_owner,posX,posY,factory,
                           BLUE_SNIPER,GREEN_SNIPER,RED_SNIPER,YELLOW_SNIPER);
                break;
            case LAZER:
                createUnit(cod_unit,unit_owner,posX,posY,factory,
                           BLUE_LASER,GREEN_LASER,RED_LASER,YELLOW_LASER);
                break;
            case LASER:
                units_map[cod_unit] = factory.createUnit(LASER_BULLET,cod_unit,posX,posY);
                break;
        }

    }
}

void Units_Protected::createUnit(int cod_unit, int unit_owner, int posX, int posY, Factory_Units &factory,
                                 FlagsUnitType blue, FlagsUnitType green, FlagsUnitType red, FlagsUnitType yellow) {

    switch(unit_owner){
        case OWNER_BLUE:
            units_map[cod_unit]= factory.createUnit(blue,cod_unit,posX,posY);
            break;
        case OWNER_GREEN:
            units_map[cod_unit] = factory.createUnit(green,cod_unit,posX,posY);
            break;
        case OWNER_RED:
            units_map[cod_unit] = factory.createUnit(red,cod_unit,posX,posY);
            break;
        case OWNER_YELLOW:
            units_map[cod_unit] = factory.createUnit(yellow,cod_unit,posX,posY);
            break;
    }
}