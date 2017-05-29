#include "createBehaviour.h"


createBehaviour::createBehaviour(int factory_c){
	tech_level = 1;
	type_f = factory_c;
	switch (factory_c){
		case VEHICLE_FACTORY:
			unit_code = JEEP;
			time_count = JEEP_F_TIME;
			unit_time = JEEP_F_TIME;
			return;
		case FORT:
		case ROBOT_FACTORY:
			unit_code = GRUNT;
			time_count = GRUNT_F_TIME;
			unit_time = GRUNT_F_TIME;
			return;
		default:
			return;
	}
}

//actualizo el tiempo restante para la creacion de la unidad
//que pasa con el tech level?
int createBehaviour::actualize(int t){
	if (time_count == 0) {
		time_count = unit_time;
		}
	time_count -= t;
	if (time_count == 0) return unit_code;
	return -1;
}


void createBehaviour::createVehicleFactory(int unit_c){
	switch (unit_c){
		case (JEEP):
			unit_code = JEEP;
			time_count = JEEP_F_TIME;
			unit_time = JEEP_F_TIME;
			return;
		case (LIGHT_TANK):
			unit_code = LIGHT_TANK;
			time_count = LIGHT_TANK_F_TIME;
			unit_time = LIGHT_TANK_F_TIME;
			return;
		case (MEDIUM_TANK):
			unit_code = MEDIUM_TANK;
			time_count = MEDIUM_TANK_F_TIME;
			unit_time = MEDIUM_TANK_F_TIME;
			return;
		case (HEAVY_TANK):
			unit_code = HEAVY_TANK;
			time_count = HEAVY_TANK_F_TIME;
			unit_time = HEAVY_TANK_F_TIME;
			return;
		case (MML):
			unit_code = MML;
			time_count = MML_F_TIME;
			unit_time = MML_F_TIME;
			return;
		default:
			return;
	}
};

void createBehaviour::createRobotFactory(int unit_c){
	switch (unit_c){
		case (GRUNT):
			unit_code = GRUNT;
			time_count = GRUNT_F_TIME;
			unit_time = GRUNT_F_TIME;
			return;
		case (PSYCHO):
			unit_code = PSYCHO;
			time_count = PSYCHO_F_TIME;
			unit_time = PSYCHO_F_TIME;
			return;
		case (TOUGHT):
			unit_code = TOUGHT;
			time_count = TOUGHT_F_TIME;
			unit_time = TOUGHT_F_TIME;
			return;
		case (PYRO):
			unit_code = PYRO;
			time_count = PYRO_F_TIME;
			unit_time = PYRO_F_TIME;
			return;
		case (SNIPER):
			unit_code = SNIPER;
			time_count = SNIPER_F_TIME;
			unit_time = SNIPER_F_TIME;
			return;
		case (LAZER):
			unit_code = LAZER;
			time_count = LAZER_F_TIME;
			unit_time = LAZER_F_TIME;
			return;
		default:
			return;
	}
};

void createBehaviour::create(int unit_c){
	//chequear que la fabrica pueda crear la unidad correspondiente???
	if (unit_code == unit_c) return; //si quiero hacer la misma unidad retorno
	switch(type_f){
		case VEHICLE_FACTORY:
			this->createVehicleFactory(unit_c);
			return;
		case FORT:
			this->createRobotFactory(unit_c);
			this->createVehicleFactory(unit_c);
			return;
		case ROBOT_FACTORY:
			this->createRobotFactory(unit_c);
			return;
		default:
			return;
	}
}



int createBehaviour::getUnitCode(){
	return unit_code;
}