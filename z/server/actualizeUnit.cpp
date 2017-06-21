#include "actualizeUnit.h"
#include <vector>
#include "tilesListCost.h"
#include <iostream>
#include <math.h>  
#include <algorithm> 
#include "unitBuilder.h"



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
			//std::cout << "unit: " << unit_game_id << " move" << std::endl;
			move_h.moveActualize(u, mapa, 1);
			return 0;
		case ATTACKING:
			//std::cout << "unit: " << unit_game_id << " attac" << std::endl;
			attack_h.attackActualize(u, units, unit_id_count, time);
			return 0;
		case CREATING:
			//std::cout << "unit: " << unit_game_id << " creat" << std::endl;
			create_h.createActualize(u, units, unit_id_count, time, ip);
			return 0;
		case STANDING:
			//std::cout << "unit: " << unit_game_id << " stand" << std::endl;
			autoAttackActualize(u, units, mapa, time);
			return 0;
		case CHECKING_CAPTURE:
			//std::cout << "unit: " << unit_game_id << " check_capt" << std::endl;
			capture_h.checkingCaptureActualize(u, units, time, ip);
			return 0;
		case CAPTURED:
			//std::cout << "unit: " << unit_game_id << " captured" << std::endl;
			u.changeState(CHECKING_CAPTURE);
			return 0;
		case DRIVING:{
			//std::cout << "unit: " << unit_game_id << " driving" << std::endl;
			
			unit *v = u.getTarget();
			if (v->getOwner() != u.getOwner()){
				std::cout << "vehic own: " << v->getOwner() << std::endl;
				unitBuilder ub;
				unit *n_v = ub.build(v->getUnitId(), u.getOwner(), v->getX(), v->getY());
				units.insert(std::pair<int,unit*>(unit_id_count,n_v));
				unit_id_count++;
				u.instantDrive(n_v);
				v->changeState(ERASED);
				/*
				v->setPos(-200, -200);
				v->setDriver(nullptr);
				v->changeState(DEAD);
				*/ 
			}
			return 0;
			}
		case DEFEATED:
			//std::cout << "unit: " << unit_game_id << " defeated" << std::endl;
			return 0;
	}
	return 0;
}

