#ifndef ARMAMENT_H
#define ARMAMENT_H

#include "../common/constants.h"



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
