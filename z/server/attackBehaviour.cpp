#include "attackBehaviour.h"



attackBehaviour::attackBehaviour(int unit_c): arma(armament(unit_c)){
	switch (unit_c) {
		case GRUNT:
			shoot_freq = 2;
			a_range = 7;
			return;
		case PSYCHO:
			shoot_freq = 10;
			a_range = 7;
			return;
		case TOUGHT: 
			shoot_freq = 2;
			a_range = 5;
			return;
		case PYRO:
			shoot_freq = 10;
			a_range = 7;
			return;
		case SNIPER: 
			shoot_freq = 4;
			a_range = 10;
			return;
		case LAZER: 
			shoot_freq = 4;
			a_range = 7;
			return;
		case JEEP:
			shoot_freq = 6;
			a_range = 6;
			return;
		case MML: 
			shoot_freq = 2;
			a_range = 8;
			return;
		case MEDIUM_TANK:
			shoot_freq = 0.5;
			a_range = 7;
			return;
		case LIGHT_TANK:
			shoot_freq = 0.5;
			a_range = 6;
			return;
		case HEAVY_TANK:
			shoot_freq = 0.5;
			a_range = 6;
			return;
		default:
			shoot_freq = 0;
			a_range = 0;
			return;
	}
}

double attackBehaviour::getDamage(int time){
	return arma.getBaseDamage() * shoot_freq * time;
}

int attackBehaviour::getRange(){
	return a_range;
}