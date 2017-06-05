#include "captureHandler.h"


void captureHandler::checkingCaptureActualize(unit &u, std::map<int, unit*> &units, int time){
	if (!u.getTarget()){
		//chequeo por unidad cercana
		for (auto it = units.begin(); it != units.end(); ++it){
			//si la unidad esta en rango
			unit *target = it->second;
			if (u.isInRange(*target)){
				//y es un robot o vehiculo
				if (target->getClassId() == ROBOT || target->getClassId() == VEHICLE){
					//la seteo como target
					//reseteo el timer
					u.setTarget(target);
					u.resetTimer();
				}
			}
		}
	} else {
		//ya tengo unidad cercana
		//si sigue en rango
		if (u.targetIsInRange()) {
			//si el owner de la unidad 
			//es distinto al owner de la bandera
			if (!u.sameOwnerAsTarget()){
				//actualizo el timer
				u.actualizeTimer(time);
				//si se cumplio el tiempo, es capturada
				if (u.timerIsZero()){
					//actualizo tech levels de las fabricas
					this->captureActualize(u.getOwner(), u.getTargetOwner(), units);
					//seteo el owner nuevo
					u.changeOwnerForTargetOwner();
				}
			}
		} else { 
			//si no esta en rango
			u.setTarget(nullptr);
		}
	}
}


void captureHandler::captureActualize(int old_owner, int new_owner, std::map<int, unit*> &units){
	//recorro unidades
	for (auto it = units.begin(); it != units.end(); ++it){
		unit *u = it->second;
		if (u->getClassId() == BUILDING){
			//si es de viejo owner decremento tech lvlv
			if (u->getOwner() == old_owner){
				u->decreaseTechLvl();
			}
			//si es de nuevo owner incremento tech lvlv
			if (u->getOwner() == new_owner){
				u->increaseTechLvl();
			}
		}
	}
}