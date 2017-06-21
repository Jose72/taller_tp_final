#ifndef DEATHHANDLER_H
#define DEATHHANDLER_H

#include "unit.h"
#include <map>
#include "infoGame.h"
#include "gameMap.h"

class deathHandler{
	private:
		int deathVehicle(unit &u, std::map<int, unit*> &units, gameMap &mapa);
		int deathBuilding(unit &u, std::map<int, unit*> &units, int &units_count);
		int deathBridge(unit &u, std::map<int, unit*> &units, gameMap &mapa);
	public:
		int death(unit &u, std::map<int, unit*> &units, int &units_count, gameMap &mapa, infoGame &ip);
};

#endif