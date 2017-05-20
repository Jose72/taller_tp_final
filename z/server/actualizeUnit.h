#ifndef ACTUALIZEUNIT_H
#define ACTUALIZEUNIT_H

#include "unit.h"
#include "behaviour.h"
#include "gameMap.h"
#include "tile.h"



class actualizeUnit: public behaviour {
	public:
		int operator()(unit &u, gameMap &mapa, double time);
};

#endif