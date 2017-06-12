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

int getFabTimeFromUnit(int unit_c){
	switch (unit_c){
		case GRUNT:
			return GRUNT_F_TIME;
		case PSYCHO:
			return PSYCHO_F_TIME;
		case TOUGHT:
			return TOUGHT_F_TIME;
		case PYRO:
			return PYRO_F_TIME;
		case SNIPER:
			return SNIPER_F_TIME;
		case LAZER:
			return LAZER_F_TIME;
		case JEEP:
			return JEEP_F_TIME;
		case LIGHT_TANK:
			return LIGHT_TANK_F_TIME;
		case MEDIUM_TANK:
			return MEDIUM_TANK_F_TIME;
		case HEAVY_TANK:
			return HEAVY_TANK_F_TIME;
		case MML:
			return MML_F_TIME;
		default:
			return 1000;
	}
	
}


int getTechLvlFromUnit(int unit_c){
	switch (unit_c){
		case GRUNT:
			return GRUNT_TL;
		case PSYCHO:
			return PSYCHO_TL;
		case TOUGHT:
			return TOUGHT_TL;
		case PYRO:
			return PYRO_TL;
		case SNIPER:
			return SNIPER_TL;
		case LAZER:
			return LAZER_TL;
		case JEEP:
			return JEEP_TL;
		case LIGHT_TANK:
			return LIGHT_TANK_TL;
		case MEDIUM_TANK:
			return MEDIUM_TANK_TL;
		case HEAVY_TANK:
			return HEAVY_TANK_TL;
		case MML:
			return MML_TL;
		default:
			return 1000;
	}
	
}