#ifndef ATTACKHANDLER_H
#define ATTACKHANDLER_H

#include "unit.h"
#include <map>
#include <set>

class attackHandler{
	private:
		int attackBulletActualize(unit &attacker, int time);
		int attackCommonActualize(unit &attacker, std::map<int, unit*> &units, int &unit_id_c, int time);
		int autoAttackCommonActualize(unit &attacker, std::map<int, unit*> &units, int &unit_id_c, int time);
	public:
		int attackActualize(unit &attacker, std::map<int, unit*> &units, int &unit_id_c, int time);
};

#endif

