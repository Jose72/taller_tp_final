#include "Attack.h"
#include <vector>

Attack::Attack(int unit_id): arma(armament(unit_id)){
}

int Attack::operator()(unit &attacker, unit *attacked, double time){
	if (attacked){
		double t_damage = attacker.getDps() * time;
		
	}
	return 0;
}

int getDamagePerSecond(unit &){
	
}