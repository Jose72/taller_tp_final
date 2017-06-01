#include "unitBuilder.h"

unit* unitBuilder::build(int unit_code, int owner, std::vector<int> &allies, int x, int y){
	switch (unit_code){
		
		//UNIDADES
		case GRUNT:
			return new unit(unit_code, ROBOT, owner, allies, x, y, 
			GRUNT_HEALTH, STANDING, ROBOT_SPEED, GRUNT_RANGE, BALAS_D, GRUNT_SF, GRUNT_TL);
		case PSYCHO:
			return new unit(unit_code, ROBOT, owner, allies, x, y, 
			PSYCHO_HEALTH, STANDING, ROBOT_SPEED, PSYCHO_RANGE, BALAS_D, PSYCHO_SF, PSYCHO_TL);
		case TOUGHT:
			return new unit(unit_code, ROBOT, owner, allies, x, y, 
			TOUGHT_HEALTH, STANDING, ROBOT_SPEED, TOUGHT_RANGE, MISILES_D, TOUGHT_SF, TOUGHT_TL);
		case PYRO:
			return new unit(unit_code, ROBOT, owner, allies, x, y, 
			PYRO_HEALTH, STANDING, ROBOT_SPEED, PYRO_RANGE, LANZALLAMAS_D, PYRO_SF, PYRO_TL);
		case SNIPER:
			return new unit(unit_code, ROBOT, owner, allies, x, y, 
			SNIPER_HEALTH, STANDING, ROBOT_SPEED, SNIPER_RANGE, BALAS_D, SNIPER_SF, SNIPER_TL);
		case LAZER:
			return new unit(unit_code, ROBOT, owner, allies, x, y, 
			LAZER_HEALTH, STANDING, ROBOT_SPEED, LAZER_RANGE, LASER_D, LAZER_SF, LAZER_TL);
			
			
		//VEHICULOS
		case JEEP:
			return new unit(unit_code, VEHICLE, owner, allies, x, y, 
			JEEP_HEALTH, STANDING, JEEP_SPEED, JEEP_RANGE, BALAS_D, JEEP_SF, JEEP_TL);
		case LIGHT_TANK:
			return new unit(unit_code, VEHICLE, owner, allies, x, y, 
			LIGHT_TANK_HEALTH, STANDING, LIGHT_TANK_SPEED, LIGHT_TANK_RANGE, PROYECTILES_D, LIGHT_TANK_SF, LIGHT_TANK_TL);
		case MEDIUM_TANK:
			return new unit(unit_code, VEHICLE, owner, allies, x, y, 
			MEDIUM_TANK_HEALTH, STANDING, MEDIUM_TANK_SPEED, MEDIUM_TANK_RANGE, PROYECTILES_D, MEDIUM_TANK_SF, MEDIUM_TANK_TL);
		case HEAVY_TANK:
			return new unit(unit_code, VEHICLE, owner, allies, x, y, 
			HEAVY_TANK_HEALTH, STANDING, HEAVY_TANK_SPEED, HEAVY_TANK_RANGE, PROYECTILES_D, HEAVY_TANK_SF, HEAVY_TANK_TL);
		case MML:
			return new unit(unit_code, VEHICLE, owner, allies, x, y, 
			MML_HEALTH, STANDING, MML_SPEED, MML_RANGE, MISILES_D, MML_SF, MML_TL);
			
			
		//EDIFICIOS
		case FORT:
			return new unit(unit_code, BUILDING, owner, allies, x, y, 
			BUILDING_HEALTH, CREATING, 0, 0, 0, 0, 1);
		case VEHICLE_FACTORY:
			return new unit(unit_code, BUILDING, owner, allies, x, y, 
			BUILDING_HEALTH, CREATING, 0, 0, 0, 0, 1);
		case ROBOT_FACTORY:
			return new unit(unit_code, BUILDING, owner, allies, x, y, 
			BUILDING_HEALTH, CREATING, 0, 0, 0, 0, 1);
			
			
		default:
			return nullptr;
	}
}


unit* unitBuilder::build(int unit_code, int x, int y){
	std::vector<int> al;
	switch (unit_code){
		//BANDERA
		case FLAG:
			return new unit(unit_code, VEHICLE, 0, al, x, y, 
			0, NO_STATE, 0, FLAG_RANGE, 0, 0, 0);
			
			
		//BALAS
		case LLAMAS:
			return new unit(unit_code, BULLET, 0, al, x, y, 
			0, MOVING, BALA_SPEED, 0, LANZALLAMAS_D, 0, 0);
		case HCP:
			return new unit(unit_code, BULLET, 0, al, x, y, 
			0, MOVING, BALA_SPEED, 0, PROYECTILES_D, 0, 0);
		case LASER:
			return new unit(unit_code, BULLET, 0, al, x, y, 
			0, MOVING, BALA_SPEED, 0, LASER_D, 0, 0);
		case MISIL:
			return new unit(unit_code, BULLET, 0, al, x, y, 
			0, MOVING, BALA_SPEED, 0, MISILES_D, 0, 0);
			
			
		default:
			return nullptr;
		}
}