#ifndef DEATHHANDLER_H
#define DEATHHANDLER_H

#include "unit.h"
#include <map>
#include "infoGame.h"

class deathHandler{
	private:
		int deathVehicle(unit &u, std::map<int, unit*> &units);
		int deathBuilding(unit &u, std::map<int, unit*> &units, int &units_count);
	public:
		int death(unit &u, std::map<int, unit*> &units, int &units_count, infoGame &ip);
};

#endif