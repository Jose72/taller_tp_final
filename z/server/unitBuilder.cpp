#include "unitBuilder.h"

#define NO_OWNER 0

#define ROB_SIZE_D 16
#define FLAG_SIZE_D 16
#define BULLET_SIZE_D 16
#define VEH_SIZE_D 32
#define FORT_SIZE_W 160
#define FORT_SIZE_H 192
#define FAC_SIZE_D 96
#define BRIDGE_H1 64
#define BRIDGE_W1 64
#define BRIDGE_H2 64
#define BRIDGE_W2 64
#define BLOCK_SIZE_D 32

unitBuilder::unitBuilder(infoUnits &u_info): u_info(u_info) {
	u_info.print();
	}

unit* unitBuilder::build(int unit_code, int owner, int x, int y){
	switch (unit_code){
		//ROBOTS
		case GRUNT:
		case PSYCHO:
		case TOUGHT:
		case PYRO:
		case SNIPER:
		case LAZER:
		//VEHICULOS
		case JEEP:
		case LIGHT_TANK:
		case MEDIUM_TANK:
		case HEAVY_TANK:
		case MML:
			return new unit(
			unit_code,
			u_info.getClassCode(unit_code), 
			u_info.getHeight(unit_code),
			u_info.getWidth(unit_code),
			owner,
			x,
			y,
			u_info.getHealth(unit_code),
			STANDING,
			u_info.getBlocking(unit_code),
			u_info.getSpeed(unit_code),
			u_info.getRange(unit_code) * 5,
			u_info.getDamage(unit_code),
			u_info.getExplosive(unit_code),
			u_info.getShootTime(unit_code),
			u_info.getUnitToCreate(unit_code),
			u_info.getTechLvl(unit_code)
			);
		
		//EDIFICIOS
		case FORT:
			return new unit(
			unit_code,
			u_info.getClassCode(unit_code), 
			u_info.getHeight(unit_code),
			u_info.getWidth(unit_code),
			owner,
			x,
			y,
			u_info.getHealth(unit_code),
			CREATING,
			u_info.getBlocking(unit_code),
			u_info.getSpeed(unit_code),
			u_info.getRange(unit_code) * 5,
			u_info.getDamage(unit_code),
			u_info.getExplosive(unit_code),
			u_info.getFabTime(u_info.getUnitToCreate(unit_code)),
			u_info.getUnitToCreate(unit_code),
			u_info.getTechLvl(unit_code)
			);
		case VEHICLE_FACTORY:
		case ROBOT_FACTORY:
			return new unit(
			unit_code,
			u_info.getClassCode(unit_code), 
			u_info.getHeight(unit_code),
			u_info.getWidth(unit_code),
			owner,
			x,
			y,
			u_info.getHealth(unit_code),
			NO_STATE,
			u_info.getBlocking(unit_code),
			u_info.getSpeed(unit_code),
			u_info.getRange(unit_code),
			u_info.getDamage(unit_code),
			u_info.getExplosive(unit_code),
			u_info.getFabTime(u_info.getUnitToCreate(unit_code)),
			u_info.getUnitToCreate(unit_code),
			u_info.getTechLvl(unit_code)
			);
			
		//BANDERA
		case FLAG:
			return new unit(
			unit_code,
			u_info.getClassCode(unit_code), 
			u_info.getHeight(unit_code),
			u_info.getWidth(unit_code),
			NO_OWNER,
			x,
			y,
			u_info.getHealth(unit_code),
			CHECKING_CAPTURE,
			u_info.getBlocking(unit_code),
			u_info.getSpeed(unit_code),
			u_info.getRange(unit_code),
			u_info.getDamage(unit_code),
			u_info.getExplosive(unit_code),
			u_info.getShootTime(unit_code),
			u_info.getUnitToCreate(unit_code),
			u_info.getTechLvl(unit_code)
			);
			
		//PUENTE
		case BRIDGE_V:
		case BRIDGE_H:
		case BRIDGE_V_WOOD:
		case BRIDGE_H_WOOD:
		//BLOQUES
		case ROCK:
		case ICE_B:
			return new unit(
			unit_code,
			u_info.getClassCode(unit_code), 
			u_info.getHeight(unit_code),
			u_info.getWidth(unit_code),
			NO_OWNER,
			x,
			y,
			u_info.getHealth(unit_code),
			NO_STATE,
			u_info.getBlocking(unit_code),
			u_info.getSpeed(unit_code),
			u_info.getRange(unit_code),
			u_info.getDamage(unit_code),
			u_info.getExplosive(unit_code),
			u_info.getShootTime(unit_code),
			u_info.getUnitToCreate(unit_code),
			u_info.getTechLvl(unit_code)
			);
			
		default:
			return nullptr;
	}
}


unit* unitBuilder::build(int unit_code, int x, int y){
	switch (unit_code){
		//BANDERA
		case FLAG:
			return new unit(
			unit_code,
			u_info.getClassCode(unit_code), 
			u_info.getHeight(unit_code),
			u_info.getWidth(unit_code),
			NO_OWNER,
			x,
			y,
			u_info.getHealth(unit_code),
			CHECKING_CAPTURE,
			u_info.getBlocking(unit_code),
			u_info.getSpeed(unit_code),
			u_info.getRange(unit_code),
			u_info.getDamage(unit_code),
			u_info.getExplosive(unit_code),
			u_info.getShootTime(unit_code),
			u_info.getUnitToCreate(unit_code),
			u_info.getTechLvl(unit_code)
			);

		//BALAS
		case BALAS:
		case LLAMAS:
		case HCP:
		case LASER:
		case MISIL:
		return new unit(
			unit_code,
			u_info.getClassCode(unit_code), 
			u_info.getHeight(unit_code),
			u_info.getWidth(unit_code),
			NO_OWNER,
			x,
			y,
			u_info.getHealth(unit_code),
			MOVING,
			u_info.getBlocking(unit_code),
			u_info.getSpeed(unit_code),
			u_info.getRange(unit_code),
			u_info.getDamage(unit_code),
			u_info.getExplosive(unit_code),
			u_info.getShootTime(unit_code),
			u_info.getUnitToCreate(unit_code),
			u_info.getTechLvl(unit_code)
			);
			
		//PUENTE
		case BRIDGE_V:
		case BRIDGE_H:
		case BRIDGE_V_WOOD:
		case BRIDGE_H_WOOD:
		//BLOQUES
		case ROCK:
		case ICE_B:
			return new unit(
			unit_code,
			u_info.getClassCode(unit_code), 
			u_info.getHeight(unit_code),
			u_info.getWidth(unit_code),
			NO_OWNER,
			x,
			y,
			u_info.getHealth(unit_code),
			NO_STATE,
			u_info.getBlocking(unit_code),
			u_info.getSpeed(unit_code),
			u_info.getRange(unit_code),
			u_info.getDamage(unit_code),
			u_info.getExplosive(unit_code),
			u_info.getShootTime(unit_code),
			u_info.getUnitToCreate(unit_code),
			u_info.getTechLvl(unit_code)
			);
			
		default:
			return nullptr;
		}
}