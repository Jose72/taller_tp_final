
#include "attackHandler.h"
#include "math.h"
#include "unitBuilder.h"

int attackHandler::attackActualize(unit &attacker, int time){
	int u_class = attacker.getClassId();
	switch(u_class){
		case ROBOT:
		case VEHICLE:
			return attackCommonActualize(attacker, time);
		case BULLET:
			return attackBulletActualize(attacker, time);
		default:
			return 0;
	}
	
}


int attackHandler::attackCommonActualize(unit &attacker, int time){
	unit *attacked = attacker.getTarget();
	if (attacker.isInRange(*attacked)){
			//si me estoy moviendo me detengo
			//estaba siguiendo a la unidad para atacar
			if (attacker.isMoving()) {
				//std::cout << "me detuve" << std::endl;
				attacker.stop();
			}
			
			//actualiza el timer
			attacker.actualizeTimer(time);
			//si estoy en cond de atacar lo hago
			if (attacker.canAttack()){
				//que se haga en create
				//set create bullet
				//attacker.resetAttackTimer();
				//unitBuilder ub;
				//unit *u = ub.build(attacker.unitToCreate(), attacker.getX(), attacker.getY());
			} 
		
			//attacked->takeDamage(round(attacker.getDamage()));
		} else {
			//si no estoy en rango, seteo como destino a la unidad
			//el target se puede estar moviendo por eso hay que hacer esto cada vez
			//asi actualizar el destino
			attacker.move(attacked->getX(), attacked->getY());
			attacker.changeState(MOVING);
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