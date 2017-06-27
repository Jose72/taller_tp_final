//
// Created by mbataglia on 20/06/17.
//

#include <iostream>
#include "ConstantsInterpretor.h"
#include "SpritesPool.h"
#include "../common/constants.h"

bool isColor(FlagsUnitType a ,FlagsUnitType b ,FlagsUnitType c , FlagsUnitType d, FlagsUnitType color){
    return (color == a || color == b || color == c || color == d);
}

bool ConstantsInterpretor::isRobotUnit(int t){
    return (t == GRUNT || t == PYRO || t == LAZER || t == PSYCHO || t == TOUGHT || t == SNIPER);
}

int ConstantsInterpretor::getType(FlagsUnitType color){

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

ConstantsInterpretor::ConstantsInterpretor(){
    blue.insert(BLUE_GRUNT);
    blue.insert(JEEP_BLUE);
    blue.insert(MEDIUM_TANK_BLUE);
    blue.insert(LIGHT_TANK_BLUE);
    blue.insert(HEAVY_TANK_BLUE);
    blue.insert(MISILE_LAUNCHER_BLUE);
    blue.insert(BLUE_PSYCHO);
    blue.insert(BLUE_TOUGHT);
    blue.insert(BLUE_PYRO);
    blue.insert(BLUE_SNIPER);
    blue.insert(BLUE_LASER);

    green.insert(GREEN_GRUNT);
    green.insert(JEEP_GREEN);
    green.insert(MEDIUM_TANK_GREEN);
    green.insert(LIGHT_TANK_GREEN);
    green.insert(HEAVY_TANK_GREEN);
    green.insert(MISILE_LAUNCHER_GREEN);
    green.insert(GREEN_PSYCHO);
    green.insert(GREEN_TOUGHT);
    green.insert(GREEN_PYRO);
    green.insert(GREEN_SNIPER);
    green.insert(GREEN_LASER);

    red.insert(RED_GRUNT);
    red.insert(JEEP_RED);
    red.insert(MEDIUM_TANK_RED);
    red.insert(LIGHT_TANK_RED);
    red.insert(HEAVY_TANK_RED);
    red.insert(MISILE_LAUNCHER_RED);
    red.insert(RED_PSYCHO);
    red.insert(RED_TOUGHT);
    red.insert(RED_PYRO);
    red.insert(RED_SNIPER);
    red.insert(RED_LASER);

    yellow.insert(YELLOW_GRUNT);
    yellow.insert(JEEP_YELLOW);
    yellow.insert(MEDIUM_TANK_YELLOW);
    yellow.insert(LIGHT_TANK_YELLOW);
    yellow.insert(HEAVY_TANK_YELLOW);
    yellow.insert(MISILE_LAUNCHER_YELLOW);
    yellow.insert(YELLOW_PSYCHO);
    yellow.insert(YELLOW_TOUGHT);
    yellow.insert(YELLOW_PYRO);
    yellow.insert(YELLOW_SNIPER);
    yellow.insert(YELLOW_LASER);

}

int ConstantsInterpretor::getColor(FlagsUnitType flag){
    if(blue.find(flag) != blue.end()){
        return TEAM_BLUE;
    }

    if(green.find(flag) != green.end()){
        return TEAM_GREEN;
    }

    if(yellow.find(flag) != yellow.end()){
        return TEAM_YELLOW;
    }

    if(red.find(flag) != red.end()){
        return TEAM_RED;
    }

    return NO_COLOR;
}

std::string ConstantsInterpretor::idToString(int id){
    switch (id){
        case GRUNT:
            return "Grunt";
            break;
        case JEEP:
            return "Jeep";
            break;
        case MEDIUM_TANK:
            return "Medium tank";
            break;
        case LIGHT_TANK:
            return "Light Tank";
            break;
        case HEAVY_TANK:
            return "Heavy Tank";
            break;
        case MML:
            return "MML";
            break;
        case PSYCHO:
            return "Psycho";
            break;
        case TOUGHT:
            return "Tought";
            break;
        case PYRO:
            return "Pyro";
            break;
        case SNIPER:
            return "Sniper";
            break;
        case LAZER:
            return "Lazer";
            break;
        case FORT:
            return "Fort";
            break;
        case ROBOT_FACTORY:
            return "Robot Factory";
            break;
        case VEHICLE_FACTORY:
            return "Vehicle Factory";
            break;
        default:
            return std::to_string(id);

    }

}