#ifndef MOVEHANDLER_H
#define MOVEHANDLER_H

#include "unit.h"
#include "gameMap.h"
#include <map>
#include <set>

class moveHandler{
	private:
		int moveBulletActualize(unit &u, double time);
		int moveCommonActualize(unit &u, gameMap &mapa, double time);
	public:
		int moveActualize(unit &u, gameMap &mapa, double time);
};

#endif

