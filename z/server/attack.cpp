#include "attack.h"
#include <vector>
#include "math.h"
#include "constants.h"
#include <iostream>

Attack::Attack(int unit_id): arma(armament(unit_id)){
	switch (unit_id) {
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

int Attack::operator()(unit *attacker, unit *attacked, double time){
	if (attacked){
		double t_damage = arma.getBaseDamage() * shoot_freq * time;
		std::cout << "t_dama: " << t_damage << std::endl;
		std::cout << "range: " << a_range << std::endl;
		if (attacker->isInRange(*attacked, a_range)){
			attacked->takeDamage(round(t_damage));
		} else {
			//si no estoy en rango, seteo como destino a la unidad
			attacker->move(attacked->getX(), attacked->getY());
		}
		
	}
	return 0;
}
