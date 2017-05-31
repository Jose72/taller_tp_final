#include "constants.h"


int getClassCodeFromUnit(int unit_c){
	switch (unit_c){
		case GRUNT:
		case PSYCHO:
		case TOUGHT:
		case PYRO:
		case SNIPER:
		case LAZER:
			return ROBOT;
		case JEEP:
		case LIGHT_TANK:
		case MEDIUM_TANK:
		case HEAVY_TANK:
		case MML:
			return VEHICLE;
		case FORT:
		case VEHICLE_FACTORY:
		case ROBOT_FACTORY:
			return BUILDING;
		default:
			return -1;
	}
	
}

int getSpeedFromUnit(int unit_c){
	switch (unit_c){
		case GRUNT:
		case PSYCHO:
		case TOUGHT:
		case PYRO:
		case SNIPER:
		case LAZER:
			return ROBOT_SPEED;
		case JEEP:
			return JEEP_SPEED;
		case LIGHT_TANK:
			return LIGHT_TANK_SPEED;
		case MEDIUM_TANK:
			return MEDIUM_TANK_SPEED;
		case HEAVY_TANK:
			return HEAVY_TANK_SPEED;
		case MML:
			return MML_SPEED;
		default:
			return -1;
	}
	
}

int getHealthFromUnit(int unit_c){
	switch (unit_c){
		case GRUNT:
			return GRUNT_HEALTH;
		case PSYCHO:
			return PSYCHO_HEALTH;
		case TOUGHT:
			return TOUGHT_HEALTH;
		case PYRO:
			return PYRO_HEALTH;
		case SNIPER:
			return SNIPER_HEALTH;
		case LAZER:
			return LAZER_HEALTH;
		case JEEP:
			return JEEP_HEALTH;
		case LIGHT_TANK:
			return LIGHT_TANK_HEALTH;
		case MEDIUM_TANK:
			return MEDIUM_TANK_HEALTH;
		case HEAVY_TANK:
			return HEAVY_TANK_HEALTH;
		case MML:
			return MML_HEALTH;
		case FORT:
		case VEHICLE_FACTORY:
		case ROBOT_FACTORY:
			return BUILDING_HEALTH;
		default:
			return -1;
	}
	
}