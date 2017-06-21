
#include "attackHandler.h"
#include "math.h"
#include "unitBuilder.h"
#include <iostream>

int attackHandler::attackActualize(unit &attacker, std::map<int, unit*> &units, int &unit_id_c, int time){
	int u_class = attacker.getClassId();
	if (attacker.autoAttackEnabled()){
		switch(u_class){
			case ROBOT:
			case VEHICLE:
				return autoAttackCommonActualize(attacker, units, unit_id_c, time);
			default:
				return 0;
		}
		
	} else {
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
}

//ATAQUE COMUN
int attackHandler::attackCommonActualize(unit &attacker, std::map<int, unit*> &units, int &unit_id_c, int time){
	unit *attacked = attacker.getTarget();
	if (attacker.targetIsInRange() && attacker.targetIsAttackable()){
			//actualiza el timer
			attacker.actualizeTimer(time);
			//si estoy en cond de atacar lo hago
			if (attacker.canAttack()){
				//si usa balas, es instantaneo
				//sino, creo una bullet y la inserto
				if (attacker.unitToCreate() == BALAS){
					attacked->takeDamage(round(attacker.getDamage()),attacker.isExplosiveDamage());
				} else {
					//std::cout << "crea bullet" << std::endl;
					unitBuilder ub;
					unit *u = ub.build(attacker.unitToCreate(), attacker.getCenterX(), attacker.getCenterY());
					u->attack(attacked);
					units.insert(std::pair<int,unit*>(unit_id_c,u));
					unit_id_c++;//incremento id_units
					//reseteo el timer
					attacker.resetTimer();
				}
			} 
		} else {
			//si no estoy en rango(y no es autoataque), seteo como destino a la unidad
			//el target se puede estar moviendo por eso hay que hacer esto cada vez
			attacker.moveToTarget();
		}
		return 0;
}


//AUTO-ATAQUE COMUN
int attackHandler::autoAttackCommonActualize(unit &attacker, std::map<int, unit*> &units, int &unit_id_c, int time){
	unit *attacked = attacker.getTarget();
	if (attacker.getOwner() == 0) return 1;
	if (attacker.targetIsInRange() && attacker.targetIsEnemy()){
			//actualiza el timer
			attacker.actualizeTimer(time);
			//si estoy en cond de atacar lo hago
			if (attacker.canAttack()){
				//si usa balas, es instantaneo
				//sino, creo una bullet y la inserto
				if (attacker.unitToCreate() == BALAS){
					attacked->takeDamage(round(attacker.getDamage()),attacker.isExplosiveDamage());
				} else {
					//std::cout << "crea bullet" << std::endl;
					unitBuilder ub;
					unit *u = ub.build(attacker.unitToCreate(), attacker.getX(), attacker.getY());
					u->attack(attacked);
					units.insert(std::pair<int,unit*>(unit_id_c,u));
					unit_id_c++;//incremento id_units
					//reseteo el timer
					attacker.resetTimer();
				}
			} 
	} else {
		//si me fui de rango
		//remuevo el target y quedo en STANDING
		//(autoataque sigue encendido)
		//std::cout << "reset autoataq" << std::endl;
		attacker.removeTarget(attacked);
		attacker.changeState(STANDING);
		attacker.resetTimer();
		}
		return 0;
}


int attackHandler::attackBulletActualize(unit &attacker, int time){
	unit *attacked = attacker.getTarget();
	
	//si el taget enta en rango
	//recibe daño
	if (attacker.targetIsInRange() && attacker.targetIsAttackable()){
			attacked->takeDamage(round(attacker.getDamage()),attacker.isExplosiveDamage());
	}
	
	//la bala muere cuando ataca
	attacker.changeState(DEAD);
	return 0;
}