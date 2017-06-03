#include "deathHandler.h"

int deathHandler::death(unit &u, std::map<int, unit*> &units){
	int status = u.getState();
	if (status != DEAD) return 1;
	int class_unit = u.getClassId();
	switch(class_unit){
		case VEHICLE:
		default:
			
		break;
	}
	u.noticeFollowersOfDeath();
	return 0;
	
}