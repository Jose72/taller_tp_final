#ifndef ATTACKHANDLER_H
#define ATTACKHANDLER_H

#include "unit.h"
#include <map>
#include "unitBuilder.h"

class attackHandler{
	private:
		unitBuilder &ub;
		int attackBulletActualize(unit &attacker, int time);
		int attackCommonActualize(unit &attacker, std::map<int, unit*> &units, 
			int &unit_id_c, int time);
		int autoAttackCommonActualize(unit &attacker, std::map<int, 
			unit*> &units, int &unit_id_c, int time);
	public:
		attackHandler(unitBuilder &ub);
		int attackActualize(unit &attacker, std::map<int, unit*> &units, 
			int &unit_id_c, int time);
};

#endif

