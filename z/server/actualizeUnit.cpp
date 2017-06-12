#include "actualizeUnit.h"
#include <vector>
#include "tilesListCost.h"
#include <iostream>
#include <math.h>  
#include <algorithm> 



int autoAttackActualize(unit &attacker, std::map<int, unit*> &units, gameMap &mapa, double time){
	int class_u = attacker.getClassId();
	//si no es robot o vehiculo no hay autoataque (necesario????)
	if (class_u != ROBOT && class_u != VEHICLE) return 1;
	//recorro el vect de unidades
	for (auto it = units.begin(); it != units.end(); ++it){
		unit *target = it->second;
		//chequeo quien es el dueño de la unidad
		
		if (attacker.isEnemy(*target) && 
		(target->getClassId() == ROBOT || target->getClassId() == VEHICLE || target->getClassId() == BUILDING) && 
		!target->isDriving()){
			//si esta en rango
			if (attacker.isInRange(*target)){
				attacker.setAutoAttack(target);
				return 0;
			}
		}
	}
	return 1;
}

int actualizeUnit::operator()(int unit_game_id, unit &u, std::map<int, unit*> &units, gameMap &mapa, double time, int &unit_id_count, infoPlayers &ip){
	//std::cout << "start actu-----------" << std::endl;
	int state = u.getState();
	switch(state){
		case MOVING:
			std::cout << "unit: " << unit_game_id << " move" << std::endl;
			move_h.moveActualize(u, mapa, 0.5);
			return 0;
		case ATTACKING:
			std::cout << "unit: " << unit_game_id << " attac" << std::endl;
			attack_h.attackActualize(u, units, unit_id_count, time);
			return 0;
		case CREATING:
			//pendiente: chequear la cant de unidades antes de crear
			std::cout << "unit: " << unit_game_id << " creat" << std::endl;
			create_h.createActualize(u, units, unit_id_count, time);
			return 0;
		case STANDING:
			std::cout << "unit: " << unit_game_id << " stand" << std::endl;
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
		case DRIVING:
			//std::cout << "unit: " << unit_game_id << " driving" << std::endl;
			return 0;
		case DEFEATED:
			//std::cout << "unit: " << unit_game_id << " defeated" << std::endl;
			return 0;
	}
	//std::cout << "end actu---------" << std::endl;
	return 0;
}

