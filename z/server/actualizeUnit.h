#ifndef ACTUALIZEUNIT_H
#define ACTUALIZEUNIT_H

#include "unit.h"
#include "behaviour.h"
#include "gameMap.h"
#include "tile.h"

enum unit_speed {
		ROBOT_SPEED = 4,
		JEPP_SPEED = 8,
		MEDIUM_TANK_SPEED = 5,
		LIGHT_TANK_SPEED = 6,
		HEAVY_TANK_SPEED = 5,
		MML_SPEED = 5
	};

class actualizeUnit: public behaviour {
	public:
		void run(unit &u, gameMap &mapa);
};

#endif