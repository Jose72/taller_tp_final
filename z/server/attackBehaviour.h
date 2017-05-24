#ifndef ATTACKBEHAVIOUR_H
#define ATTACKBEHAVIOUR_H

#include "behaviour.h"
#include "armament.h"


class attackBehaviour: public behaviour {
	private:
		armament arma;
		double shoot_freq;
		int a_range;
	public:
		attackBehaviour(int unit_c);
		double getDamage(int t);
		int getRange();
};

#endif