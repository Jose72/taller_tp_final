#ifndef ARMAMENT_H
#define ARMAMENT_H

#include "unit.h"

enum weapon_damage {BALAS = 2, LANZALLAMAS = 10, PROYECTILES = 20, 
LASER = 10, MISILES = 25};

class armament{
	private:
		int damage;
		bool explosive;
	public:
		armament(int unit_code);
		bool isExplosive();
		int getBaseDamage();
};

#endif
