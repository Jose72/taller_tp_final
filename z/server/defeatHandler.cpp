#include "defeatHandler.h"
#include <iostream>


//si el edificio esta muerto no hace falta hacer nada
//si el fuerte esta vivo (perdio porquwe se quedo sin undiades)
//lo paso a DEAD (el deathHandler hara lo suyo)
//si es una fabrica, pasa a NO_STATE (para que no costruya y luego sea tomada por otro)
int defeatHandler::defeatBuilding(unit *u){
	if (!u->isAlive()) return -1;
	if (u->getUnitId() == FORT){
		u->changeState(DEAD);
	} else {
		u->changeState(NO_STATE);
	}
	return 0;
}


//robots y vehiculos pasan a DEFEATED 
//banderas quedan igual
int defeatHandler::defeatPlayer(int t_code, std::map<int, unit*> &units){
	for (auto it = units.begin(); it != units.end(); ++it){
		unit *u = it->second;
		if (u->getOwner() == t_code){
			int c = u->getClassId();
			switch(c){
				case BUILDING:
					defeatBuilding(u);
					return 0;
				case FLAG_C:
					return 0;
				default:
					u->changeState(DEFEAT);
					return 0;
			}
		}
	}
	return 0;
}