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
		//calculo daño
		double t_damage = arma.getBaseDamage() * shoot_freq * time;
		//chequeo si esta en rango
		if (attacker->isInRange(*attacked, a_range)){
			//si me estoy moviendo me detengo
			//estaba siguiendo a la unidad para atacar
			if (attacker->isMoving()) {
				//std::cout << "me detuve" << std::endl;
				attacker->stop();
			}
			attacked->takeDamage(round(t_damage));
		} else {
			//si no estoy en rango, seteo como destino a la unidad
			//el target se puede estar moviendo por eso hay que hacer esto cada vez
			//asi actualizar el destino
			//hay que usar un bool para saber si es auto-ataque y no hacer esto
			//std::cout << "seteo target como destino" << std::endl;
			attacker->move(attacked->getX(), attacked->getY());
		}
		
	}
	return 0;
}

/* autoatatcque

autoattack(unit* attacker, std::vector<unit*> targets){
	//recorro el vect de unidades
	for (auto it = targets.begin(); it != targets.end(); ++it){
	
		//chequeo quien es el dueño de la unidad
		if ((*it)->isEnemy(attacker->Owner())){
			//si esta en rango
			if (attacker->isInRange((*it))){
			
				attack(attacker, (*it));
				//le pego y ya, no sigo con los demas
				return;
				
				// en vez de esto se podria setear la unidad como target
				// con un booleano que indique autoataque
				// y que la actualizacion de ataque haga el resto
			
			}
		
		
		}
	}
}

*/