#include "createBehaviour.h"


createBehaviour::createBehaviour(int unit_c){
	tech_level = 1;
	switch (unit_c){
		case VEHICLE_FACTORY:
			unit_code = JEEP;
			time_count = JEEP_F_TIME;
			return;
		case FORT:
		case ROBOT_FACTORY:
		default:
			unit_code = GRUNT;
			time_count = GRUNT_F_TIME;
			return;
	}
}

//actualizo el tiempo restante para la creacion de la unidad
//que pasa con el tech level?
int createBehaviour::actualize(int t){
	time_count -= t;
	if (time_count == 0) return unit_code;
	return -1;
}

void createBehaviour::create(int unit_c){
	//chequear que la fabrica pueda crear la unidad correspondiente???
	if (unit_code != unit_c) { //si quiero hacer otra unidad
		unit_code = unit_c;
		//seteo tiempo
	}
}

int createBehaviour::getUnitCode(){
	return unit_code;
}