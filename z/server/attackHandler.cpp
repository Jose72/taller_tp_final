
#include "attackHandler.h"
#include "math.h"

void attackHandler::attackActualize(unit &attacker, std::map<int, unit*> &units, int time){
	unit *attacked = attacker.getTarget();
	int u_class = attacker.getClassId();
	
	/*
	switch(u_class){
		case ROBOT:
		case VEHICLE:
		case BULLET:
		default:
	}
	
	if (attacker.isInRange(*attacked, attacker.attackRange())){
			//si me estoy moviendo me detengo
			//estaba siguiendo a la unidad para atacar
			if (attacker.isMoving()) {
				//std::cout << "me detuve" << std::endl;
				attacker.stop();
			}
			attacked->takeDamage(round(attacker.getDamage()));
		} else {
			//si no estoy en rango, seteo como destino a la unidad
			//el target se puede estar moviendo por eso hay que hacer esto cada vez
			//asi actualizar el destino
			//hay que usar un bool para saber si es auto-ataque y no hacer esto
			//std::cout << "seteo target como destino" << std::endl;
			attacker.move(attacked->getX(), attacked->getY());
		}
		return;
	*/
}