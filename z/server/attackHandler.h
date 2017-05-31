#ifndef ATTACKHANDLER_H
#define ATTACKHANDLER_H

#include "unit.h"
#include <map>

class attackHandler{
	public:
		void attackActualize(unit &attacker, std::map<int, unit*> &units, int time);
};

#endif

