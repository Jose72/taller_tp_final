#ifndef DEATHHANDLER_H
#define DEATHHANDLER_H

#include "unit.h"
#include <map>

class deathHandler{
	private:
		int deathVehicle(unit &ur, std::map<int, unit*> &units);
	public:
		int death(unit &u, std::map<int, unit*> &units);
};

#endif