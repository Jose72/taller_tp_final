#include "infoPlayer.h"
#include <map>
#include <iostream>
		
		

infoPlayer::infoPlayer(int id, serverProtocol *prot): player_id(id), prot(prot), current_tech_lvl(1){}

infoPlayer::infoPlayer(int id): player_id(id), current_tech_lvl(1){}

int infoPlayer::getPlayerId(){
	return player_id;
}

bool infoPlayer::maxUnitsReached(){
	if (units_count == MAX_UNITS) return true;
	return false;
}

void infoPlayer::incrementUnitsCount(){
	units_count++;
}

void infoPlayer::decrementUnitsCount(){
	units_count--;
}

bool infoPlayer::fortAlive(){
	if (fort && fort->isAlive()) return true;
	return false;
}

void infoPlayer::initialize(unit *fort,int units_count){
	this->fort = fort;
	this->units_count = units_count;
}

int infoPlayer::updateVictoryConditions(){
	if ((units_count == 0 || !this->fortAlive())) {
		state = DEFEAT;
		return DEFEAT;
	}
	return OK;
}

bool infoPlayer::isDefeated(){
	return (state == DEFEAT);
}
