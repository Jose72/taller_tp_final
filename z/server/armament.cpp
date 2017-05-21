#include "armament.h"

armament::armament(int code){
	switch (code) {
		case GRUNT:
			damage = BALAS;
			explosive = false;
		case PSYCHO:
		case SNIPER: 
		case JEEP:
			damage = BALAS;
			explosive = false;
		
		case TOUGHT: 
			damage = MISILES;
			explosive = true;
		
		case PYRO:
		case MML: 
			damage = MISILES;
			explosive = true;
		
		case LAZER: 
			damage = LASER;
			explosive = false;
			
		case MEDIUM_TANK:
		case LIGHT_TANK:
		case HEAVY_TANK:
			damage = PROYECTILES;
			explosive = true;
			
		default:
			damage = 0;
			explosive = false;
	}
}

bool armament::isExplosive(){
	return explosive;
}

int armament::getBaseDamage(){
	return damage;
}