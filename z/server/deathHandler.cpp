#include "deathHandler.h"
#include <iostream>
#include "unitBuilder.h"

int deathHandler::deathBuilding(unit &u, std::map<int, unit*> &units, int &id_units_count){
	if (u.getUnitId() == FORT) {
		unitBuilder ub;
		unit *f = ub.build(FLAG, u.getCenterX(), u.getCenterY());
		f->changeOwner(u.getOwner());
		units.insert(std::pair<int,unit*>(id_units_count,f));
		id_units_count++;
	}
	u.changeState(DESTROYED);
	return 0;
}

int deathHandler::deathVehicle(unit &u, std::map<int, unit*> &units){
	std::cout << "murio vehicle" << std::endl;
	unit* a = u.getDriver();
	std::cout << "vehicle driver"  << u.getDriver() << std::endl;
	u.releaseDriver();
	return 0;
}

int deathHandler::death(unit &u, std::map<int, unit*> &units, int &id_unit_counter, infoGame &ip){
	int status = u.getState();
	if (status != DEAD) return 1;
	int class_unit = u.getClassId();
	switch(class_unit){
		case ROBOT:
			ip.decrementUnitsCount(u.getOwner());
			break;
		case VEHICLE:
			deathVehicle(u, units);
			ip.decrementUnitsCount(u.getOwner());
			break;
		case BUILDING:
			deathBuilding(u, units, id_unit_counter);
			break;
		default:
		break;
	}
	u.stopFollowers();
	return 0;
	
}