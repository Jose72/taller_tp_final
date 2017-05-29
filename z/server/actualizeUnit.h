#ifndef ACTUALIZEUNIT_H
#define ACTUALIZEUNIT_H

#include "unit.h"
#include "behaviour.h"
#include "gameMap.h"
#include "tile.h"
#include <map>

int aStart(tile *orig, tile *dest, gameMap &gmap, int unit_code, 
std::vector<tile*> &path);

class actualizeUnit: public behaviour {
	public:
		int operator()(unit &u, std::map<int, unit*> &units, gameMap &mapa, 
		double time, int &unit_id_count);
};

#endif