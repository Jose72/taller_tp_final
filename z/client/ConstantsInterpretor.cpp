//
// Created by mbataglia on 20/06/17.
//

#include <iostream>
#include "ConstantsInterpretor.h"
#include "SpritesPool.h"
#include "../common/constants.h"

bool isColor(FlagsUnitType a ,FlagsUnitType b ,
             FlagsUnitType c , FlagsUnitType d, FlagsUnitType color){
    return (color == a || color == b || color == c || color == d);
}

bool ConstantsInterpretor::isRobotUnit(int t){
    return (t == GRUNT || t == PYRO || t == LAZER ||
            t == PSYCHO || t == TOUGHT || t == SNIPER);
}

int ConstantsInterpretor::getType(FlagsUnitType color){

    if(isColor(BLUE_GRUNT,GREEN_GRUNT,RED_GRUNT,YELLOW_GRUNT,color))
        return GRUNT;

    if(isColor(JEEP_BLUE,JEEP_GREEN,JEEP_RED,JEEP_YELLOW,color))
        return JEEP;

    if(isColor(MEDIUM_TANK_BLUE,MEDIUM_TANK_GREEN,MEDIUM_TANK_RED,
               MEDIUM_TANK_YELLOW,color))
        return MEDIUM_TANK;

    if(isColor(LIGHT_TANK_BLUE,LIGHT_TANK_GREEN,LIGHT_TANK_RED,
               LIGHT_TANK_YELLOW,color))
        return LIGHT_TANK;

    if(isColor(HEAVY_TANK_BLUE,HEAVY_TANK_GREEN,HEAVY_TANK_RED,
               HEAVY_TANK_YELLOW,color))
        return HEAVY_TANK;

    if(isColor(MISILE_LAUNCHER_BLUE,MISILE_LAUNCHER_GREEN,
               MISILE_LAUNCHER_RED,MISILE_LAUNCHER_YELLOW,color))
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

    grunt.insert(GREEN_GRUNT);
    grunt.insert(RED_GRUNT);
    grunt.insert(YELLOW_GRUNT);
    grunt.insert(BLUE_GRUNT);

    jeep.insert(JEEP_GREEN);
    jeep.insert(JEEP_BLUE);
    jeep.insert(JEEP_RED);
    jeep.insert(JEEP_YELLOW);

    medium_tank.insert(MEDIUM_TANK_BLUE);
    medium_tank.insert(MEDIUM_TANK_GREEN);
    medium_tank.insert(MEDIUM_TANK_RED);
    medium_tank.insert(MEDIUM_TANK_YELLOW);

    light_tank.insert(LIGHT_TANK_BLUE);
    light_tank.insert(LIGHT_TANK_GREEN);
    light_tank.insert(LIGHT_TANK_RED);
    light_tank.insert(LIGHT_TANK_YELLOW);

    heavy_tank.insert(HEAVY_TANK_BLUE);
    heavy_tank.insert(HEAVY_TANK_GREEN);
    heavy_tank.insert(HEAVY_TANK_RED);
    heavy_tank.insert(HEAVY_TANK_YELLOW);

    misile_launcher.insert(MISILE_LAUNCHER_BLUE);
    misile_launcher.insert(MISILE_LAUNCHER_GREEN);
    misile_launcher.insert(MISILE_LAUNCHER_YELLOW);
    misile_launcher.insert(MISILE_LAUNCHER_RED);

    psycho.insert(BLUE_PSYCHO);
    psycho.insert(RED_PSYCHO);
    psycho.insert(YELLOW_PSYCHO);
    psycho.insert(GREEN_PSYCHO);

    tought.insert(BLUE_TOUGHT);
    tought.insert(GREEN_TOUGHT);
    tought.insert(YELLOW_TOUGHT);
    tought.insert(RED_TOUGHT);

    pyro.insert(BLUE_PYRO);
    pyro.insert(RED_PYRO);
    pyro.insert(YELLOW_PYRO);
    pyro.insert(GREEN_PYRO);

    sniper.insert(BLUE_SNIPER);
    sniper.insert(YELLOW_SNIPER);
    sniper.insert(GREEN_SNIPER);
    sniper.insert(RED_SNIPER);

    laser.insert(BLUE_LASER);
    laser.insert(GREEN_LASER);
    laser.insert(RED_LASER);
    laser.insert(YELLOW_LASER);

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

std::string ConstantsInterpretor::flagToString(FlagsUnitType flag){
    if(flag == FORT_ALIVE){
        return "Fort";
    }

    if(flag == FACTORY_ROBOTS_ALIVE){
        return "Robot Factory";
    }

    if(flag == FACTORY_VEHICLES_ALIVE){
        return "Vehicle Factory";
    }

    if(grunt.find(flag) != grunt.end()){
        return "Grunt";
    }

    if(jeep.find(flag) != jeep.end()){
        return "Jeep";
    }

    if(medium_tank.find(flag) != medium_tank.end()){
        return "Medium Tank";
    }

    if(light_tank.find(flag) != light_tank.end()){
        return "Light Tank";
    }

    if(heavy_tank.find(flag) != heavy_tank.end()){
        return "Heavy Tank";
    }

    if(misile_launcher.find(flag) != misile_launcher.end()){
        return "MML";
    }

    if(psycho.find(flag) != psycho.end()){
        return "Psycho";
    }

    if(tought.find(flag) != tought.end()){
        return "Tought";
    }

    if(pyro.find(flag) != pyro.end()){
        return "Pyro";
    }

    if(sniper.find(flag) != sniper.end()){
        return "Sniper";
    }

    if(laser.find(flag) != laser.end()){
        return "Lazer";
    }

    return std::to_string(flag);

}

std::string ConstantsInterpretor::flagToWeapon(FlagsUnitType flag){
    if(flag == FORT_ALIVE){
        return "Nothing";
    }

    if(flag == FACTORY_ROBOTS_ALIVE){
        return "Nothing";
    }

    if(flag == FACTORY_VEHICLES_ALIVE){
        return "Nothing";
    }

    if(grunt.find(flag) != grunt.end()){
        return "Bullets";
    }

    if(jeep.find(flag) != jeep.end()){
        return "Bullets";
    }

    if(medium_tank.find(flag) != medium_tank.end()){
        return "High caliber projectiles";
    }

    if(light_tank.find(flag) != light_tank.end()){
        return "High caliber projectiles";
    }

    if(heavy_tank.find(flag) != heavy_tank.end()){
        return "High caliber projectiles";
    }

    if(misile_launcher.find(flag) != misile_launcher.end()){
        return "Missiles";
    }

    if(psycho.find(flag) != psycho.end()){
        return "Bullets";
    }

    if(tought.find(flag) != tought.end()){
        return "Missiles";
    }

    if(pyro.find(flag) != pyro.end()){
        return "Flamethrower";
    }

    if(sniper.find(flag) != sniper.end()){
        return "Bullets";
    }

    if(laser.find(flag) != laser.end()){
        return "Lazer";
    }

    return std::to_string(flag);

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