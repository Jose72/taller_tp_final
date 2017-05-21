#ifndef ATTACK_H
#define ATTACK_H

#include "behaviour.h"
#include "armament.h"
#include "unit.h"
#include <vector>


class Attack: public behaviour {
	private:
		armament arma;
		double shoot_freq;
		int range;
	public:
		Attack(int unit_id);
		int operator()(unit *attacker, unit *attacked, double time);
};

#endif