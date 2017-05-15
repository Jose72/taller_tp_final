#ifndef UNIT_H
#define UNIT_H

#include "armament.h"

#define DAMAGE_TAKEN 0
#define UNIT_DEAD 1

class unit {
	private:
		armament arma;
		int shoot_freq; //en segundos
		int range;
		double health;
		int fab_time; //en segundos
		int min_tech_lvl;
	public:
		unit(int arma_code, int shoot_f, int range, double h, 
		int f_time, int t_lvl);
		double getDamage(int time); //necesito un tiempo para calcular el daño
		int receiveDamage(double dam);
};

#endif
