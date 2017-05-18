#include "actualizeUnit.h"


void actualizeUnit::run(unit &u, gameMap &mapa){
	int c_id = u.getClassId();
	//muevo la unidad
	if (u.isMoving()){
		switch(c_id) {
			case ROBOT:
				
				break;
			case VEHICLE:
				break;
			default:
				break;
		}
	}
}

