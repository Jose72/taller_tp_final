#include "deathHandler.h"

int deathHandler::deathBuilding(unit &u, std::map<int, unit*> &units){
	if (u.getUnitId() == FORT) u.releaseFlag();
	u.changeState(DESTROYED);
	return 0;
}

int deathHandler::deathVehicle(unit &u, std::map<int, unit*> &units){
	u.releaseDriver();
	return 0;
}

int deathHandler::death(unit &u, std::map<int, unit*> &units){
	int status = u.getState();
	if (status != DEAD) return 1;
	int class_unit = u.getClassId();
	switch(class_unit){
		case VEHICLE:
			break;
		case BUILDING:
			deathBuilding(u, units);
		default:
		break;
	}
	u.stopFollowers();
	return 0;
	
}