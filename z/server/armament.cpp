#include "armament.h"
#include <iostream>

armament::armament(int code){
	switch (code) {
		case GRUNT:
		case PSYCHO:
		case SNIPER: 
		case JEEP:
			damage = BALAS;
			explosive = false;
			return;
		case TOUGHT: 
			damage = MISILES;
			explosive = true;
			return;
		case PYRO:
		case MML: 
			damage = MISILES;
			explosive = true;
			return;
		case LAZER: 
			damage = LASER;
			explosive = false;
			return;
		case MEDIUM_TANK:
		case LIGHT_TANK:
		case HEAVY_TANK:
			damage = PROYECTILES;
			explosive = true;
			return;
		default:
			damage = 0;
			explosive = false;
			return;
	}
}

bool armament::isExplosive(){
	return explosive;
}

int armament::getBaseDamage(){
	return damage;
}