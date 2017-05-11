#ifndef PATHFINDER_H
#define PATHFINDE_H

#include "tile.h"
#include "tilesListCost.h"
#include "gameMap.h"
#include <vector>

int a_start(tile &orig, tile &dest, gameMap &gmap, int unit_code, 
std::vector<tile> &path);

#endif