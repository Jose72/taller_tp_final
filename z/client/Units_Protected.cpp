#include <iostream>
#include "Units_Protected.h"
#include "../common/Lock.h"
#include "SoundManager.h"

#define NO_OWNER 0
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

void Units_Protected::animate(int limitXL, int limitXR, int limitYU, int limitYD , SDL_Rect cameraRect, SoundManager &soundManager) {
    tLock(this->mut);
    std::map<int, Unit*>::iterator it;
    for (it = units_map.begin();it != units_map.end() ; ++it) {
        if (BETWEEN(it->second->get_posx(), limitXL, limitXR)) {
            if (BETWEEN(it->second->get_posy(), limitYU, limitYD)) {
                if((it->second->get_type() == BRIDGE_CONCRETE_HORIZONTAL)||
                   (it->second->get_type() == BRIDGE_CONCRETE_VERTICAL)||
                   (it->second->get_type() == BRIDGE_WOOD_HORIZONTAL) ||
                   (it->second->get_type() == BRIDGE_WOOD_VERTICAL)) {
                    it->second->animate(cameraRect);
                }

            }
        }
    }
    for (it = units_map.begin();it != units_map.end() ; ++it) {
        if (BETWEEN(it->second->get_posx(), limitXL, limitXR)) {
            if (BETWEEN(it->second->get_posy(), limitYU, limitYD)) {
                if((it->second->get_type() != BRIDGE_CONCRETE_HORIZONTAL)&&
                   (it->second->get_type() != BRIDGE_CONCRETE_VERTICAL)&&
                   (it->second->get_type() != BRIDGE_WOOD_HORIZONTAL) &&
                   (it->second->get_type() != BRIDGE_WOOD_VERTICAL)){
                    if(it->second->get_type() == PYRO_BULLET){
                        soundManager.playGuns(PYRO_BULLET);
                    }

                    if(it->second->get_type() == LASER_BULLET){
                        soundManager.addLaserBullet(it->second->get_unit_code());
                    }

                    if(it->second->get_type() == TOUGHT_BULLET){
                        soundManager.addToughBullet(it->second->get_unit_code());
                    }

                    it->second->animate(cameraRect);
                }
            }
        }
    }
    soundManager.playToughBullets();
    soundManager.playLaser();
}

Unit* Units_Protected::selectUnit(int dx1, int dx2, int dy1, int dy2, bool &found, int id_client) {
    tLock(this->mut);
    Unit *unitSelected;
    found = false;
    std::map<int, Unit*>::iterator it;
    for (it = units_map.begin();it != units_map.end() ; ++it) {
        if (BETWEEN(it->second->get_posx(), dx1, dx2)) {
            if (BETWEEN(it->second->get_posy(), dy1, dy2)) {
                if(it->second->get_owner() == id_client){
                    unitSelected = it->second;
                    found = true;
                }
            }
        }
    }
    return unitSelected;
}

Unit* Units_Protected::selectEnemy(int dx1, int dx2, int dy1, int dy2, Action &action, int id_client) {
    tLock(this->mut);
    Unit *enemy;
    std::map<int, Unit*>::iterator it;
    action = MOVE;
    for (it = units_map.begin();it != units_map.end() ; ++it) {
        if (BETWEEN(it->second->get_posx(), dx1, dx2)) {
            if (BETWEEN(it->second->get_posy(), dy1, dy2)) {
                if(it->second->get_owner() != id_client){
                    if((it->second->get_type() == HEAVY_TANK_EMPTY) ||
                       (it->second->get_type() == MEDIUM_TANK_EMPTY)||
                       (it->second->get_type() == LIGHT_TANK_EMPTY) ||
                       (it->second->get_type() == JEEP_EMPTY)||
                       (it->second->get_type() == MISILE_LAUNCHER_EMPTY)){
                        action = DRIVE;
                    } else{
                        action = ATTACK;
                    }
                    enemy = it->second;
                }
            }
        }
    }
    return enemy;
}

void Units_Protected::cleanDeadUnits() {
    tLock(this->mut);
    std::map<int, Unit*>::iterator it;
    for (it = units_map.begin();it != units_map.end() ; ++it) {
        if (it->second->get_state() == DEAD2){
            units_map.erase(it->first);
        }
    }

}


bool Units_Protected::createIsNotExist(int cod_unit, int unit_type, int unit_owner, int posX, int posY,
                                       Factory_Units &factory) {
    tLock(this->mut);
    bool result = false;
    if(units_map.find(cod_unit) == units_map.end()){
        switch (unit_type){

             case JEEP:
                createVehicle(cod_unit,unit_owner,posX,posY,factory,
                              JEEP_BLUE,
                              JEEP_GREEN,
                              JEEP_RED,
                              JEEP_YELLOW,
                              JEEP_EMPTY);
                result = true;
                break;

            case MEDIUM_TANK:
                createVehicle(cod_unit,unit_owner,posX,posY,factory,
                              MEDIUM_TANK_BLUE,
                              MEDIUM_TANK_GREEN,
                              MEDIUM_TANK_RED,
                              MEDIUM_TANK_YELLOW,
                              MEDIUM_TANK_EMPTY);
                result = true;
                break;
            case LIGHT_TANK:
                createVehicle(cod_unit,unit_owner,posX,posY,factory,
                              LIGHT_TANK_BLUE,
                              LIGHT_TANK_GREEN,
                              LIGHT_TANK_RED,
                              LIGHT_TANK_YELLOW,
                              LIGHT_TANK_EMPTY);
                result = true;
                break;
            case HEAVY_TANK:
                createVehicle(cod_unit,unit_owner,posX,posY,factory,
                              HEAVY_TANK_BLUE,
                              HEAVY_TANK_GREEN,
                              HEAVY_TANK_RED,
                              HEAVY_TANK_YELLOW,
                              HEAVY_TANK_EMPTY);
                result = true;
                break;

            case MML:
                createVehicle(cod_unit,unit_owner,posX,posY,factory,
                              MISILE_LAUNCHER_BLUE,
                              MISILE_LAUNCHER_GREEN,
                              MISILE_LAUNCHER_RED,
                              MISILE_LAUNCHER_YELLOW,
                              MISILE_LAUNCHER_EMPTY);
                result = true;
                break;

            case GRUNT:
                createUnit(cod_unit,unit_owner,posX,posY,factory,
                           BLUE_GRUNT,GREEN_GRUNT,RED_GRUNT,YELLOW_GRUNT);
                result = true;
                break;

            case PSYCHO:
                createUnit(cod_unit,unit_owner,posX,posY,factory,
                           BLUE_PSYCHO,GREEN_PSYCHO,RED_PSYCHO,YELLOW_PSYCHO);
                result = true;
                break;
            case TOUGHT:
                createUnit(cod_unit,unit_owner,posX,posY,factory,
                           BLUE_TOUGHT,GREEN_TOUGHT,RED_TOUGHT,YELLOW_TOUGHT);
                result = true;
                break;
            case PYRO:
                createUnit(cod_unit,unit_owner,posX,posY,factory,
                           BLUE_PYRO,GREEN_PYRO,RED_PYRO,YELLOW_PYRO);
                result = true;
                break;
            case SNIPER:
                createUnit(cod_unit,unit_owner,posX,posY,factory,
                           BLUE_SNIPER,GREEN_SNIPER,RED_SNIPER,YELLOW_SNIPER);
                result = true;
                break;
            case LAZER:
                createUnit(cod_unit,unit_owner,posX,posY,factory,
                           BLUE_LASER,GREEN_LASER,RED_LASER,YELLOW_LASER);
                result = true;
                break;

            case FORT:
                units_map[cod_unit] = factory.createUnit(FORT_ALIVE,cod_unit,posX,posY, unit_owner);
                break;

            case ROBOT_FACTORY:
                units_map[cod_unit] = factory.createUnit(FACTORY_ROBOTS_ALIVE,cod_unit,posX,posY, unit_owner);
                break;

            case VEHICLE_FACTORY:
                units_map[cod_unit] = factory.createUnit(FACTORY_VEHICLES_ALIVE,cod_unit,posX,posY,unit_owner);
                break;

            case LASER:
                units_map[cod_unit] = factory.createUnit(LASER_BULLET,cod_unit,posX,posY,unit_owner);
                break;

            case LLAMAS:
                units_map[cod_unit] = factory.createUnit(PYRO_BULLET,cod_unit,posX,posY, unit_owner);
                break;

            case MISIL:
                units_map[cod_unit] = factory.createUnit(TOUGHT_BULLET,cod_unit,posX,posY, unit_owner);
                break;

            case HCP:
                units_map[cod_unit] = factory.createUnit(HCP_BULLET,cod_unit,posX,posY,unit_owner);
                break;

            case BRIDGE_V:
                units_map[cod_unit] = factory.createUnit(BRIDGE_CONCRETE_VERTICAL,cod_unit,posX,posY,unit_owner);
                break;

            case BRIDGE_H:
                units_map[cod_unit] = factory.createUnit(BRIDGE_CONCRETE_HORIZONTAL,cod_unit,posX,posY,unit_owner);
                break;

            case ROCK:
                units_map[cod_unit] = factory.createUnit(ROCK_BLOCK,cod_unit,posX,posY,unit_owner);
                break;

            case ICE_B:
                units_map[cod_unit] = factory.createUnit(ICE_BLOCK,cod_unit,posX,posY,unit_owner);
                break;

            case FLAG:
                units_map[cod_unit] = factory.createUnit(COLORLESS_FLAG,cod_unit,posX,posY, unit_owner);
                break;
        }

    }
    return result;
}

void Units_Protected::createUnit(int cod_unit, int unit_owner, int posX, int posY, Factory_Units &factory,
                                 FlagsUnitType blue, FlagsUnitType green, FlagsUnitType red, FlagsUnitType yellow) {

    switch(unit_owner){
        case OWNER_BLUE:
            units_map[cod_unit]= factory.createUnit(blue,cod_unit,posX,posY,unit_owner);
            break;
        case OWNER_GREEN:
            units_map[cod_unit] = factory.createUnit(green,cod_unit,posX,posY,unit_owner);
            break;
        case OWNER_RED:
            units_map[cod_unit] = factory.createUnit(red,cod_unit,posX,posY,unit_owner);
            break;
        case OWNER_YELLOW:
            units_map[cod_unit] = factory.createUnit(yellow,cod_unit,posX,posY,unit_owner);
            break;
    }
}



void Units_Protected::createVehicle(int cod_unit, int unit_owner, int posX, int posY,
                                    Factory_Units &factory,
                                    FlagsUnitType blue,
                                    FlagsUnitType green,
                                    FlagsUnitType red,
                                    FlagsUnitType yellow,
                                    FlagsUnitType empty) {

    switch(unit_owner){
        case NO_OWNER:
            units_map[cod_unit]= factory.createUnit(empty,cod_unit,posX,posY,unit_owner);
            break;
        case OWNER_BLUE:
            units_map[cod_unit]= factory.createUnit(blue,cod_unit,posX,posY,unit_owner);
            break;
        case OWNER_GREEN:
            units_map[cod_unit] = factory.createUnit(green,cod_unit,posX,posY,unit_owner);
            break;
        case OWNER_RED:
            units_map[cod_unit] = factory.createUnit(red,cod_unit,posX,posY,unit_owner);
            break;
        case OWNER_YELLOW:
            units_map[cod_unit] = factory.createUnit(yellow,cod_unit,posX,posY,unit_owner);
            break;
    }
}

void Units_Protected::endGame(int winner) {
    tLock(this->mut);
    std::map<int, Unit*>::iterator it;
    for (it = units_map.begin();it != units_map.end() ; ++it) {
        if (it->second->get_owner() == winner){
            it->second->set_state(CELEBRATE);
        }else{
            it->second->set_state(DRINKING);
        }
    }

}
