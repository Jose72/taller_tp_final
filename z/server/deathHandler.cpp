#include "deathHandler.h"
#include <iostream>
#include "unitBuilder.h"


//si es un fuerte creo la bandera
//paso el edificio a DESTROYED 
int deathHandler::deathBuilding(unit &u, std::map<int, unit*> &units, int &id_units_count){
	if (u.getUnitId() == FORT) {
		unitBuilder ub;
		unit *f = ub.build(FLAG, u.getX(), u.getY());
		f->changeOwner(u.getOwner());
		units.insert(std::pair<int,unit*>(id_units_count,f));
		id_units_count++;
	}
	u.changeState(DESTROYED);
	return 0;
}

int deathHandler::deathVehicle(unit &u, std::map<int, unit*> &units, gameMap &mapa){
	//std::cout << "murio vehicle" << std::endl;
	unit* a = u.getDriver();
	//std::cout << "vehicle driver"  << u.getDriver() << std::endl;
	//std::cout << "x: " << a->getX() << "Y: " << a->getY() <<std::endl;
	if (a){
	a->setPos(u.getX(), u.getY());
		std::cout << "---------------------------------: " << std::endl;
		std::cout << "x: " << a->getX() << "Y: " << a->getY() <<std::endl;
		a->setTarget(nullptr);
		//si el conductor esta en una casilla imposible
		//(se destruyo puente y tiene que a aparecer ahi, va a DEAD)
		if (mapa.impossibleTile(a->getX(), a->getY(), ROBOT)){
			a->changeState(DEAD);
			std::cout << "MUERTO---------------------------------: " << std::endl;
		} else {
			a->changeState(STANDING);
			std::cout << "STANDING---------------------------------: " << std::endl;
		}
	}
	//u.releaseDriver();
	return 0;
}

int deathHandler::deathBridge(unit &u, std::map<int, unit*> &units, gameMap &mapa){
	//seteo las casilla como bloqueadas
	mapa.setUnitAsBlocking(&u);
	//me fijo que unidades estaban arriba y las pongo en muerte
	for (auto it = units.begin(); it != units.end(); ++it){
		unit *a = it->second;
		int a_class = a->getClassId();
		if (u.hasOnTop(a)){
			if (a_class == ROBOT){
				a->changeState(DEAD);
			}
			if (a_class == VEHICLE){
				//unit *d = a->getDriver();
				a->changeState(DEAD);
			}
		}
	}
	//paso a destroyed
	u.changeState(DESTROYED);
	return 0;
}

int deathHandler::death(unit &u, std::map<int, unit*> &units, int &id_unit_counter, gameMap &mapa, infoGame &ip){
	int status = u.getState();
	if (status != DEAD) return 1;
	int class_unit = u.getClassId();
	switch(class_unit){
		case ROBOT:
			ip.decrementUnitsCount(u.getOwner());
			break;
		case VEHICLE:
			deathVehicle(u, units, mapa);
			//ip.decrementUnitsCount(u.getOwner());
			break;
		case BUILDING:
			deathBuilding(u, units, id_unit_counter);
			break;
		case BRIDGE_C:
			deathBridge(u, units, mapa);
			break;
		default:
		break;
	}
	u.stopFollowers();
	return 0;
	
}