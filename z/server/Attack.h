#ifndef ATTACK_H
#define ATTACK_H

#include "unit.h"
#include "behaviour.h"
#include "gameMap.h"
#include "tile.h"
#include "armament.h"
#include <vector>
/*
enum damage_units {GRUNT, PSYCHO, TOUGHT , PYRO, SNIPER, LASER, 
JEEP, MEDIUM_TANK, LIGHT_TANK, HEAVY_TANK, MML};
*/

class Attack: public behaviour {
	private:
		armament arma;
	public:
		Attack(int unit_id);
		int operator()(unit &attacker, unit *attacked, double time);
};

#endif