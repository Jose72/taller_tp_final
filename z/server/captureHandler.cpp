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
					std::cout << "flag target: " << it->first << std::endl;
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
				u.actualizeCaptureTimer(time);
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

