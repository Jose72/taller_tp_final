//
// Created by mbataglia on 20/06/17.
//

#include <iostream>
#include "ColorToType.h"
#include "SpritesPool.h"
#include "../common/constants.h"

bool isColor(FlagsUnitType a ,FlagsUnitType b ,FlagsUnitType c , FlagsUnitType d, FlagsUnitType color){
    return (color == a || color == b || color == c || color == d);
}

int ColorToType::getType(FlagsUnitType color){

    if(isColor(BLUE_GRUNT,GREEN_GRUNT,RED_GRUNT,YELLOW_GRUNT,color))
        return GRUNT;

    if(isColor(JEEP_BLUE,JEEP_GREEN,JEEP_RED,JEEP_YELLOW,color))
        return JEEP;

    if(isColor(MEDIUM_TANK_BLUE,MEDIUM_TANK_GREEN,MEDIUM_TANK_RED,MEDIUM_TANK_YELLOW,color))
        return MEDIUM_TANK;

    if(isColor(LIGHT_TANK_BLUE,LIGHT_TANK_GREEN,LIGHT_TANK_RED,LIGHT_TANK_YELLOW,color))
        return LIGHT_TANK;

    if(isColor(HEAVY_TANK_BLUE,HEAVY_TANK_GREEN,HEAVY_TANK_RED,HEAVY_TANK_YELLOW,color))
        return HEAVY_TANK;

    if(isColor(MISILE_LAUNCHER_BLUE,MISILE_LAUNCHER_GREEN,MISILE_LAUNCHER_RED,MISILE_LAUNCHER_YELLOW,color))
        return MML;

    if(isColor(BLUE_PSYCHO,GREEN_PSYCHO,RED_PSYCHO,YELLOW_PSYCHO,color))
        return PSYCHO;

    if(isColor(BLUE_TOUGHT,GREEN_TOUGHT,RED_TOUGHT,YELLOW_TOUGHT,color))
        return TOUGHT;

    if(isColor(BLUE_PYRO,GREEN_PYRO,RED_PYRO,YELLOW_PYRO,color))
        return PYRO;

    if(isColor(BLUE_SNIPER,GREEN_SNIPER,RED_SNIPER,YELLOW_SNIPER,color))
        return SNIPER;


    if(isColor(BLUE_LASER,GREEN_LASER,RED_LASER,YELLOW_LASER,color))
        return LAZER;

    if(color == FORT_ALIVE){
        return FORT;
    }

    if(color == FACTORY_ROBOTS_ALIVE){
        return ROBOT_FACTORY;
    }

    if(color == FACTORY_VEHICLES_ALIVE){
        return VEHICLE_FACTORY;
    }

    return GRUNT;
}