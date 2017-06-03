
#include "attackHandler.h"
#include "math.h"
#include "unitBuilder.h"
#include <iostream>

int attackHandler::attackActualize(unit &attacker, std::map<int, unit*> &units, int &unit_id_c, int time){
	int u_class = attacker.getClassId();
	switch(u_class){
		case ROBOT:
		case VEHICLE:
			return attackCommonActualize(attacker, units, unit_id_c, time);
		case BULLET:
			return attackBulletActualize(attacker, time);
		default:
			return 0;
	}
	
}


int attackHandler::attackCommonActualize(unit &attacker, std::map<int, unit*> &units, int &unit_id_c, int time){
	unit *attacked = attacker.getTarget();
	if (attacker.isInRange(*attacked)){
			//actualiza el timer
			attacker.actualizeTimer(time);
			//si estoy en cond de atacar lo hago
			if (attacker.canAttack()){
				//creo una bullet y la inserto
				std::cout << "crea bullet" << std::endl;
				unitBuilder ub;
				unit *u = ub.build(attacker.unitToCreate(), attacker.getX(), attacker.getY());
				u->attack(attacked);
				units.insert(std::pair<int,unit*>(unit_id_c,u));
				unit_id_c++;//incremento id_units
				//reseteo el timer
				attacker.resetTimer();
			} 
		} else {
			//si no estoy en rango, seteo como destino a la unidad
			//el target se puede estar moviendo por eso hay que hacer esto cada vez
			attacker.move(attacked->getX(), attacked->getY());
		}
		return 0;
}

//si la bala impacto, se muere y retorno 1
int attackHandler::attackBulletActualize(unit &attacker, int time){
	unit *attacked = attacker.getTarget();
	
	//si el taget enta en rango y esta vivo
	//recibe daño
	if (attacker.isInRange(*attacked) && attacked->isAlive()){
			attacked->takeDamage(round(attacker.getDamage()));
	}
	
	//la bala muere caundoa ataca
	attacker.changeState(DEAD);
	return 0;
	
	
	/*
	//si llego al destino
	if (!attacker.isMoving()){
			//si el taget enta en rango y esta vivo
			//recibe daño
			if (attacker.isInRange(*attacked) && attacked->isAlive()){
				attacked->takeDamage(round(attacker.getDamage()));
			}
			//si llego a destino la bala muere
			return 1;
		} 
	
	return 0;
	*/
}