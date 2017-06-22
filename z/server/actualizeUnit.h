#ifndef ACTUALIZEUNIT_H
#define ACTUALIZEUNIT_H

#include "unit.h"
#include "gameMap.h"
#include "tile.h"
#include "moveHandler.h"
#include "attackHandler.h"
#include "createHandler.h"
#include "captureHandler.h"
#include "unitBuilder.h"
#include "infoUnits.h"
#include <map>
#include <set>
#include "infoPlayer.h"

int aStart(tile *orig, tile *dest, gameMap &gmap, int unit_code, 
std::vector<tile*> &path);

class actualizeUnit {
		unitBuilder &ub;
		infoUnits &u_info;
		
		moveHandler move_h;
		attackHandler attack_h;
		createHandler create_h;
		captureHandler capture_h;
	public:
		actualizeUnit(unitBuilder &ub, infoUnits &u_info);
		int operator()(int unit_game_id, unit &u, std::map<int, unit*> &units, gameMap &mapa, 
		double time, int &unit_id_count, infoGame &ip);
};

#endif