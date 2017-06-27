//
// Created by mbataglia on 20/06/17.
//

#ifndef Z_COLORTOTYPE_H
#define Z_COLORTOTYPE_H

#define TEAM_BLUE 0
#define TEAM_GREEN 1
#define TEAM_RED 2
#define TEAM_YELLOW 3
#define NO_COLOR 4

#include <set>
#include "SpritesPool.h"

class ConstantsInterpretor {
private:
    std::set<FlagsUnitType> blue;
    std::set<FlagsUnitType> green;
    std::set<FlagsUnitType> red;
    std::set<FlagsUnitType> yellow;
    std::set<FlagsUnitType> grunt;
    std::set<FlagsUnitType> jeep;
    std::set<FlagsUnitType> medium_tank;
    std::set<FlagsUnitType> light_tank;
    std::set<FlagsUnitType> heavy_tank;
    std::set<FlagsUnitType> misile_launcher;
    std::set<FlagsUnitType> psycho;
    std::set<FlagsUnitType> tought;
    std::set<FlagsUnitType> pyro;
    std::set<FlagsUnitType> sniper;
    std::set<FlagsUnitType> laser;

public:
    int getType(FlagsUnitType color);
    ConstantsInterpretor();
    bool isRobotUnit(int t);
    int getColor(FlagsUnitType);
    std::string idToString(int id);

    std::string flagToString(FlagsUnitType);
};


#endif //Z_COLORTOTYPE_H
