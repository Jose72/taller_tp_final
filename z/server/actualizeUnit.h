#ifndef ACTUALIZEUNIT_H
#define ACTUALIZEUNIT_H

#include "unit.h"
#include "behaviour.h"
#include "gameMap.h"
#include "tile.h"
#include "moveHandler.h"
#include "attackHandler.h"
#include "createHandler.h"
#include "captureHandler.h"
#include <map>
#include <set>

int aStart(tile *orig, tile *dest, gameMap &gmap, int unit_code, 
std::vector<tile*> &path);

class actualizeUnit: public behaviour {
		moveHandler move_h;
		attackHandler attack_h;
		createHandler create_h;
		captureHandler capture_h;
	public:
		int operator()(int unit_game_id, unit &u, std::map<int, unit*> &units, gameMap &mapa, 
		double time, int &unit_id_count, std::set<int> &dead_unit, std::set<int> &actualized_units);
};

#endif