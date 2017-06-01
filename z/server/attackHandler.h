#ifndef ATTACKHANDLER_H
#define ATTACKHANDLER_H

#include "unit.h"
#include <map>
#include <set>

class attackHandler{
	private:
		int attackBulletActualize(unit &attacker, int time);
		int attackCommonActualize(unit &attacker, int time);
	public:
		int attackActualize(unit &attacker, int time);
};

#endif

