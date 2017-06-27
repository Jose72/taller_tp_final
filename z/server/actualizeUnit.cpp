#include "actualizeUnit.h"
#include <vector>
#include <iostream>
#include <math.h>  
#include <algorithm> 
#include "unitBuilder.h"

actualizeUnit::actualizeUnit(unitBuilder &ub, infoUnits &u_info): ub(ub), u_info(u_info), attack_h(ub), create_h(ub, u_info) {}

int autoAttackActualize(unit &attacker, std::map<int, unit*> &units, gameMap &mapa, double time){
	int class_u = attacker.getClassId();
	//si no es robot o vehiculo no hay autoataque (necesario????)
	if (class_u != ROBOT && class_u != VEHICLE) return 1;
	//recorro el vect de unidades
	for (auto it = units.begin(); it != units.end(); ++it){
		unit *target = it->second;
		//chequeo quien es el dueño de la unidad
		
		if (attacker.isEnemy(target) && (target->isAlive()) &&
		(target->getClassId() == ROBOT || target->getClassId() == VEHICLE || target->getClassId() == BUILDING)){
			//si esta en rango
			if (attacker.isInRange(*target)){
				//std::cout << "target in range" << it->first << std::endl;
				attacker.setAutoAttack(target);
				return 0;
			}
		}
	}
	return 1;
}

int actualizeUnit::operator()(int unit_game_id, unit &u, std::map<int, unit*> &units, gameMap &mapa, double time, int &unit_id_count, infoGame &ip){
	int state = u.getState();
	switch(state){
		case MOVING:
			move_h.moveActualize(u, mapa, time / 100);
			return 0;
		case ATTACKING:
			attack_h.attackActualize(u, units, unit_id_count, time);
			return 0;
		case CREATING:
			create_h.createActualize(u, units, unit_id_count, time, ip);
			return 0;
		case STANDING:
			autoAttackActualize(u, units, mapa, time);
			return 0;
		case CHECKING_CAPTURE:
			capture_h.checkingCaptureActualize(u, units, time, ip);
			return 0;
		case CAPTURED:
			u.changeState(CHECKING_CAPTURE);
			return 0;
		case READY_TO_DIE:
			u.changeState(DEAD);
			return 0;
		case DRIVING:{
			//si el vehiculo que conduzco tiene owner 0 (recien entro en DRIVING)
			//creo un nuevo vehiculo con el owner del conductor
			//y los seteo 
			//se hace por una limitacion del cliente
			//el vehiculo viejo se para a ERASED para ser borrado luego
			unit *v = u.getTarget();
			if (v->getOwner() != u.getOwner()){
				unit *n_v = ub.build(v->getUnitId(), u.getOwner(), v->getX(), v->getY());
				units.insert(std::pair<int,unit*>(unit_id_count,n_v));
				unit_id_count++;
				u.instantDrive(n_v);
				v->changeState(ERASED);
			}
			return 0;
			}
	}
	return 0;
}

