#include "terrain.h"

bool terrain::isPassable(int unit_code){
	if (unit_code == ROBOT) return passable_by_robot;
	if (unit_code == VEHICLE) return passable_by_vehicle;
	return false;
}