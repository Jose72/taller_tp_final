#ifndef MOVEHANDLER_H
#define MOVEHANDLER_H

#include "unit.h"
#include "gameMap.h"
#include <map>
#include <set>

class moveHandler{
	private:
		int moveBulletActualize(unit &u, int time);
		int moveCommonActualize(unit &u, gameMap &mapa, int time);
	public:
		int moveActualize(unit &u, gameMap &mapa, int time);
};

#endif

