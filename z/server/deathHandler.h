#ifndef DEATHHANDLER_H
#define DEATHHANDLER_H

#include "unit.h"
#include <map>
#include "infoGame.h"
#include "gameMap.h"
#include "unitBuilder.h"

class deathHandler{
	private:
		unitBuilder &ub;
		int deathVehicle(unit &u, std::map<int, unit*> &units, gameMap &mapa);
		int deathBuilding(unit &u, std::map<int, unit*> &units, int &units_count);
		int deathBridge(unit &u, std::map<int, unit*> &units, gameMap &mapa);
	public:
		deathHandler(unitBuilder &ub);
		int death(unit &u, std::map<int, unit*> &units, int &units_count, gameMap &mapa, infoGame &ip);
};

#endif