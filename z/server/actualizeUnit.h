#ifndef ACTUALIZEUNIT_H
#define ACTUALIZEUNIT_H

#include "unit.h"
#include "behaviour.h"
#include "gameMap.h"
#include "tile.h"

enum unit_speed { //veocidad (por seg)
		ROBOT_SPEED = 4,
		JEPP_SPEED = 8,
		MEDIUM_TANK_SPEED = 5,
		LIGHT_TANK_SPEED = 6,
		HEAVY_TANK_SPEED = 5,
		MML_SPEED = 5
	};

class actualizeUnit: public behaviour {
	public:
		int operator()(unit &u, gameMap &mapa, double time);
};

#endif