#ifndef ARMAMENT_H
#define ARMAMENT_H

class armament{
	private:
		int damage;
		bool explosive;
	public:
		armament(int arm_code);
		bool isExplosive();
		int getBaseDamage();
};

#endif
