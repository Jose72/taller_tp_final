#include "captureHandler.h"
#include <iostream>


void captureHandler::checkingCaptureActualize(unit &u, std::map<int, unit*> &units, int time, infoGame &ip){
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
					u.setFlagTarget(target);
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
				if (u.timerComplete()){
					//actualizo tech levels de las fabricas
					std::cout << "---------------flga captured by: "<< u.getTargetOwner() << std::endl;
					//this->captureActualize(u.getOwner(), u.getTargetOwner(), units, ip);
					ip.updateCapturedTer(u.getOwner(), u.getTargetOwner());
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


void captureHandler::captureActualize(int old_owner, int new_owner, std::map<int, unit*> &units, infoGame &ip){
	//actualizo player info
	/*
	ip.updateTechLevels(old_owner,new_owner);
	int tech_lvl_old = ip.getPlayerTechLevel(old_owner);
	int tech_lvl_new = ip.getPlayerTechLevel(new_owner);
	//recorro unidades
	for (auto it = units.begin(); it != units.end(); ++it){
		unit *u = it->second;
		if (u->getClassId() == BUILDING){
			//si es de viejo owner decremento tech lvlv
			if (u->getOwner() == old_owner && old_owner != 0){
				//std::cout << "old tech: "<< tech_lvl_old << std::endl;
				u->setTechLvl(tech_lvl_old);
			}
			//si es de nuevo owner incremento tech lvlv
			if (u->getOwner() == new_owner){
				//std::cout << "new tech: "<< tech_lvl_new << std::endl;
				u->setTechLvl(tech_lvl_new);
			}
		}
	}
	*/ 
}