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
public:
    int getType(FlagsUnitType color);
    ConstantsInterpretor();
    bool isRobotUnit(int t);
    int getColor(FlagsUnitType);
    std::string idToString(int id);
};


#endif //Z_COLORTOTYPE_H
