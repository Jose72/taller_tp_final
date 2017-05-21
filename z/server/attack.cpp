#include "attack.h"
#include <vector>
#include "math.h"
#include "constants.h"

Attack::Attack(int unit_id): arma(armament(unit_id)){
	switch (unit_id) {
		case GRUNT:
			shoot_freq = 2;
			range = 7;
		case PSYCHO:
			shoot_freq = 10;
			range = 7;
		case TOUGHT: 
			shoot_freq = 2;
			range = 5;
		case PYRO:
			shoot_freq = 10;
			range = 7;
		case SNIPER: 
			shoot_freq = 4;
			range = 10;
		case LAZER: 
			shoot_freq = 4;
			range = 7;
		case JEEP:
			shoot_freq = 6;
			range = 6;
		case MML: 
			shoot_freq = 2;
			range = 8;
		case MEDIUM_TANK:
			shoot_freq = 0.5;
			range = 7;
		case LIGHT_TANK:
			shoot_freq = 0.5;
			range = 6;
		case HEAVY_TANK:
			shoot_freq = 0.5;
			range = 6;
		default:
			shoot_freq = 0;
			range = 0;
	}
}

int Attack::operator()(unit *attacker, unit *attacked, double time){
	if (attacked){
		double t_damage = arma.getBaseDamage() * time;
		if (attacker->isInRange(*attacked, range)){
			attacked->takeDamage(round(t_damage));
		}
		
	}
	return 0;
}
