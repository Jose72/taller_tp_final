#include "unitBuilder.h"

unit* unitBuilder::build(int unit_code, int owner, int x, int y){
	switch (unit_code){
		
		//UNIDADES
		case GRUNT:
			return new unit(unit_code, ROBOT, owner, x, y, 
			GRUNT_HEALTH, STANDING, ROBOT_SPEED, GRUNT_RANGE*10, BALAS_D, GRUNT_SF, BALAS, GRUNT_TL);
		case PSYCHO:
			return new unit(unit_code, ROBOT, owner, x, y, 
			PSYCHO_HEALTH, STANDING, ROBOT_SPEED, PSYCHO_RANGE*10, BALAS_D, PSYCHO_SF, BALAS, PSYCHO_TL);
		case TOUGHT:
			return new unit(unit_code, ROBOT, owner, x, y, 
			TOUGHT_HEALTH, STANDING, ROBOT_SPEED, TOUGHT_RANGE*10, MISILES_D, TOUGHT_SF, MISIL, TOUGHT_TL);
		case PYRO:
			return new unit(unit_code, ROBOT, owner, x, y, 
			PYRO_HEALTH, STANDING, ROBOT_SPEED, PYRO_RANGE*10, LANZALLAMAS_D, PYRO_SF, LLAMAS, PYRO_TL);
		case SNIPER:
			return new unit(unit_code, ROBOT, owner, x, y, 
			SNIPER_HEALTH, STANDING, ROBOT_SPEED, SNIPER_RANGE*10, BALAS_D, SNIPER_SF, BALAS, SNIPER_TL);
		case LAZER:
			return new unit(unit_code, ROBOT, owner, x, y, 
			LAZER_HEALTH, STANDING, ROBOT_SPEED, LAZER_RANGE*10, LASER_D, LAZER_SF, LASER, LAZER_TL);
			
			
		//VEHICULOS
		case JEEP:
			return new unit(unit_code, VEHICLE, owner, x, y, 
			JEEP_HEALTH, STANDING, JEEP_SPEED, JEEP_RANGE*10, BALAS_D, JEEP_SF, BALAS, JEEP_TL);
		case LIGHT_TANK:
			return new unit(unit_code, VEHICLE, owner, x, y, 
			LIGHT_TANK_HEALTH, STANDING, LIGHT_TANK_SPEED, LIGHT_TANK_RANGE*10, PROYECTILES_D, LIGHT_TANK_SF, HCP, LIGHT_TANK_TL);
		case MEDIUM_TANK:
			return new unit(unit_code, VEHICLE, owner, x, y, 
			MEDIUM_TANK_HEALTH, STANDING, MEDIUM_TANK_SPEED, MEDIUM_TANK_RANGE*10, PROYECTILES_D, MEDIUM_TANK_SF, HCP, MEDIUM_TANK_TL);
		case HEAVY_TANK:
			return new unit(unit_code, VEHICLE, owner, x, y, 
			HEAVY_TANK_HEALTH, STANDING, HEAVY_TANK_SPEED, HEAVY_TANK_RANGE*10, PROYECTILES_D, HEAVY_TANK_SF, HCP, HEAVY_TANK_TL);
		case MML:
			return new unit(unit_code, VEHICLE, owner, x, y, 
			MML_HEALTH, STANDING, MML_SPEED, MML_RANGE*10, MISILES_D, MML_SF, MISIL, MML_TL);
			
			
		//EDIFICIOS
		case FORT:
			return new unit(unit_code, BUILDING, owner, x, y, 
			BUILDING_HEALTH, CREATING, 0, 0, 0, GRUNT_F_TIME*1000, GRUNT, 1);
		case VEHICLE_FACTORY:
			return new unit(unit_code, BUILDING, owner, x, y, 
			BUILDING_HEALTH, CREATING, 0, 0, 0, JEEP_F_TIME*1000, JEEP, 1);
		case ROBOT_FACTORY:
			return new unit(unit_code, BUILDING, owner, x, y, 
			BUILDING_HEALTH, CREATING, 0, 0, 0, GRUNT_F_TIME*1000, GRUNT, 1);
			
			
		default:
			return nullptr;
	}
}


unit* unitBuilder::build(int unit_code, int x, int y){
	switch (unit_code){
		//BANDERA
		case FLAG:
			return new unit(unit_code, FLAG_C, 0, x, y, 
			0, CHECKING_CAPTURE, 0, FLAG_RANGE*10, 0, FLAG_CAPTURE_TIME, -1, 0);
			
			
		//BALAS
		case BALAS:
			return new unit(unit_code, BULLET, 0, x, y, 
			0, MOVING, INSTA_BULLET_SPEED, 0, BALAS_D, 0, -1, 0);
		case LLAMAS:
			return new unit(unit_code, BULLET, 0, x, y, 
			0, MOVING, BULLET_SPEED, 0, LANZALLAMAS_D, 0, -1, 0);
		case HCP:
			return new unit(unit_code, BULLET, 0, x, y, 
			0, MOVING, BULLET_SPEED, 0, PROYECTILES_D, 0, -1, 0);
		case LASER:
			return new unit(unit_code, BULLET, 0, x, y, 
			0, MOVING, BULLET_SPEED, 0, LASER_D, 0, -1, 0);
		case MISIL:
			return new unit(unit_code, BULLET, 0, x, y, 
			0, MOVING, BULLET_SPEED, 0, MISILES_D, 0, -1, 0);
			
			
		default:
			return nullptr;
		}
}