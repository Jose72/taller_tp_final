#include "infoPlayer.h"
#include <map>
#include <iostream>
		
		

infoPlayer::infoPlayer(int id, serverProtocol *prot): player_id(id), prot(prot) {}

infoPlayer::infoPlayer(int id): player_id(id) {}

int infoPlayer::getPlayerId(){
	return player_id;
}

/*
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
*/
void infoPlayer::sendTeamNumber(int t){
	prot->send_team_number(t);
}