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

#include "SpritesPool.h"

class ConstantsInterpretor {
public:
    int getType(FlagsUnitType color);

    bool isRobotUnit(int t);

    int getColor(FlagsUnitType);

    std::string idToString(int id);
};


#endif //Z_COLORTOTYPE_H
