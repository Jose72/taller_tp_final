#ifndef ACTUALIZEUNIT_H
#define ACTUALIZEUNIT_H

#include "unit.h"
#include "behaviour.h"
#include "gameMap.h"
#include "tile.h"

int aStart(tile *orig, tile *dest, gameMap &gmap, int unit_code, std::vector<tile*> &path);

class actualizeUnit: public behaviour {
	public:
		int operator()(unit &u, gameMap &mapa, double time);
};

#endif