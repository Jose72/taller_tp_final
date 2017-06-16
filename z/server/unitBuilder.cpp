#include "unitBuilder.h"

#define ROB_SIZE_D 16
#define FLAG_SIZE_D 16
#define BULLET_SIZE_D 16
#define VEH_SIZE_D 32
#define FORT_SIZE_W 160
#define FORT_SIZE_H 192
#define FAC_SIZE_D 80
#define BRIDGE_H1 80
#define BRIDGE_W1 40
#define BRIDGE_H2 30
#define BRIDGE_W2 80
#define BLOCK_SIZE_D 32

unit* unitBuilder::build(int unit_code, int owner, int x, int y){
	switch (unit_code){
		
		//UNIDADES
		case GRUNT:
			return new unit(unit_code, ROBOT, ROB_SIZE_D, ROB_SIZE_D, owner, x, y, 
			GRUNT_HEALTH, STANDING, B_NOTHING, ROBOT_SPEED, GRUNT_RANGE*5, BALAS_D, false, GRUNT_SF, BALAS, GRUNT_TL);
		case PSYCHO:
			return new unit(unit_code, ROBOT, ROB_SIZE_D, ROB_SIZE_D, owner, x, y, 
			PSYCHO_HEALTH, STANDING, B_NOTHING, ROBOT_SPEED, PSYCHO_RANGE*5, BALAS_D, true, PSYCHO_SF, BALAS, PSYCHO_TL);
		case TOUGHT:
			return new unit(unit_code, ROBOT, ROB_SIZE_D, ROB_SIZE_D, owner, x, y, 
			TOUGHT_HEALTH, STANDING, B_NOTHING, ROBOT_SPEED, TOUGHT_RANGE*5, MISILES_D, true, TOUGHT_SF, MISIL, TOUGHT_TL);
		case PYRO:
			return new unit(unit_code, ROBOT, ROB_SIZE_D, ROB_SIZE_D, owner, x, y, 
			PYRO_HEALTH, STANDING, B_NOTHING, ROBOT_SPEED, PYRO_RANGE*5, LANZALLAMAS_D, true, PYRO_SF, LLAMAS, PYRO_TL);
		case SNIPER:
			return new unit(unit_code, ROBOT, ROB_SIZE_D, ROB_SIZE_D, owner, x, y, 
			SNIPER_HEALTH, STANDING, B_NOTHING, ROBOT_SPEED, SNIPER_RANGE*5, BALAS_D, true, SNIPER_SF, BALAS, SNIPER_TL);
		case LAZER:
			return new unit(unit_code, ROBOT, ROB_SIZE_D, ROB_SIZE_D, owner, x, y, 
			LAZER_HEALTH, STANDING, B_NOTHING, ROBOT_SPEED, LAZER_RANGE*5, LASER_D, false, LAZER_SF, LASER, LAZER_TL);
			
			
		//VEHICULOS
		case JEEP:
			return new unit(unit_code, VEHICLE, VEH_SIZE_D, VEH_SIZE_D, owner, x, y, 
			JEEP_HEALTH, STANDING, B_NOTHING, JEEP_SPEED, JEEP_RANGE*5, BALAS_D, false, JEEP_SF, BALAS, JEEP_TL);
		case LIGHT_TANK:
			return new unit(unit_code, VEHICLE, VEH_SIZE_D, VEH_SIZE_D, owner, x, y, 
			LIGHT_TANK_HEALTH, STANDING, B_NOTHING, LIGHT_TANK_SPEED, LIGHT_TANK_RANGE*5, PROYECTILES_D, true, LIGHT_TANK_SF, HCP, LIGHT_TANK_TL);
		case MEDIUM_TANK:
			return new unit(unit_code, VEHICLE, VEH_SIZE_D, VEH_SIZE_D, owner, x, y, 
			MEDIUM_TANK_HEALTH, STANDING, B_NOTHING, MEDIUM_TANK_SPEED, MEDIUM_TANK_RANGE*5, PROYECTILES_D, true, MEDIUM_TANK_SF, HCP, MEDIUM_TANK_TL);
		case HEAVY_TANK:
			return new unit(unit_code, VEHICLE, VEH_SIZE_D, VEH_SIZE_D, owner, x, y, 
			HEAVY_TANK_HEALTH, STANDING, B_NOTHING, HEAVY_TANK_SPEED, HEAVY_TANK_RANGE*5, PROYECTILES_D, true, HEAVY_TANK_SF, HCP, HEAVY_TANK_TL);
		case MML:
			return new unit(unit_code, VEHICLE, VEH_SIZE_D, VEH_SIZE_D, owner, x, y, 
			MML_HEALTH, STANDING, B_NOTHING, MML_SPEED, MML_RANGE*5, MISILES_D, true, MML_SF, MISIL, MML_TL);
			
			
		//EDIFICIOS
		case FORT:
			return new unit(unit_code, BUILDING, FORT_SIZE_H, FORT_SIZE_W, owner, x, y, 
			BUILDING_HEALTH, CREATING, B_BLOCK, 0, 0, 0, false, GRUNT_F_TIME*1000, GRUNT, 1);
		case VEHICLE_FACTORY:
			return new unit(unit_code, BUILDING, FAC_SIZE_D, FAC_SIZE_D, owner, x, y, 
			BUILDING_HEALTH, CREATING, B_BLOCK, 0, 0, 0, false, JEEP_F_TIME*1000, JEEP, 1);
		case ROBOT_FACTORY:
			return new unit(unit_code, BUILDING, FAC_SIZE_D, FAC_SIZE_D, owner, x, y, 
			BUILDING_HEALTH, CREATING, B_BLOCK, 0, 0, 0, false, GRUNT_F_TIME*1000, GRUNT, 1);
			
			
		default:
			return nullptr;
	}
}


unit* unitBuilder::build(int unit_code, int x, int y){
	switch (unit_code){
		//BANDERA
		case FLAG:
			return new unit(unit_code, FLAG_C, FLAG_SIZE_D, FLAG_SIZE_D, 0, x, y, 
			0, CHECKING_CAPTURE, B_NOTHING, 0, FLAG_RANGE*5, 0, false, FLAG_CAPTURE_TIME, -1, 0);
			
			
		//BALAS
		case BALAS:
			return new unit(unit_code, BULLET, BULLET_SIZE_D, BULLET_SIZE_D, 0, x, y, 
			0, MOVING, B_NOTHING, INSTA_BULLET_SPEED, BULLET_RANGE, BALAS_D, false, 0, -1, 0);
		case LLAMAS:
			return new unit(unit_code, BULLET, BULLET_SIZE_D, BULLET_SIZE_D, 0, x, y, 
			0, MOVING, B_NOTHING, BULLET_SPEED, BULLET_RANGE, LANZALLAMAS_D, true, 0, -1, 0);
		case HCP:
			return new unit(unit_code, BULLET, BULLET_SIZE_D, BULLET_SIZE_D, 0, x, y, 
			0, MOVING, B_NOTHING, BULLET_SPEED, BULLET_RANGE, PROYECTILES_D, true, 0, -1, 0);
		case LASER:
			return new unit(unit_code, BULLET, BULLET_SIZE_D, BULLET_SIZE_D, 0, x, y, 
			0, MOVING, B_NOTHING, BULLET_SPEED, BULLET_RANGE, LASER_D, false, 0, -1, 0);
		case MISIL:
			return new unit(unit_code, BULLET, BULLET_SIZE_D, BULLET_SIZE_D, 0, x, y, 
			0, MOVING, B_NOTHING, BULLET_SPEED, BULLET_RANGE, MISILES_D, true, 0, -1, 0);
			
		//PUENTE
			case BRIDGE_V:
			return new unit(unit_code, BRIDGE_C, BRIDGE_H1, BRIDGE_W1, 0, x, y, 
			0, NO_STATE, B_LET_PASS, 0, 0, 0, false, 0, -1, 0);
			case BRIDGE_H:
			return new unit(unit_code, BRIDGE_C, BRIDGE_H2, BRIDGE_W2, 0, x, y, 
			0, NO_STATE, B_LET_PASS, 0, 0, 0, false, 0, -1, 0);
		
		//BLOQUES
			case ROCK:
			return new unit(unit_code, BLOCK, BLOCK_SIZE_D, BLOCK_SIZE_D, 0, x, y, 
			0, NO_STATE, B_BLOCK, 0, 0, 0, false, 0, -1, 0);
			case ICE_B:
			return new unit(unit_code, BLOCK, BLOCK_SIZE_D, BLOCK_SIZE_D, 0, x, y, 
			0, NO_STATE, B_BLOCK, 0, 0, 0, false, 0, -1, 0);
			
		default:
			return nullptr;
		}
}