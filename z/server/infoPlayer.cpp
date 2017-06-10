#include "infoPlayer.h"
#include <map>
#include <iostream>
		
		
infoPlayers::infoPlayers(int max_p, int game_type, int teams){
	max_players = max_p;
	game_type = game_type;
	teams_count = teams;
}	
		
void infoPlayers::addNewPlayer(int id_p){
	if (players_info.size() < max_players){
		infoPlayer i(id_p);
		players_info.insert(std::pair<int,infoPlayer>(id_p,i));
	}
}

void infoPlayers::updateTechLevels(int id_old, int id_new){
	std::map<int,infoPlayer>::iterator it;
	it = players_info.find(id_old);
	(it->second).decrementTechLvl();
	it = players_info.find(id_new);
	(it->second).incrementTechLvl();
}


void infoPlayers::initializePlayer(int id_p, unit *fort, int units_count){
	std::map<int,infoPlayer>::iterator it;
	it = players_info.find(id_p);
	(it->second).initialize(fort, units_count);
}

int infoPlayers::checkVictoryConditions(int id_p){
	
	std::map<int,infoPlayer>::iterator it;
	it = players_info.find(id_p);
	int i = (it->second).checkVictoryConditions();
	if (i == DEFEAT){
			std::cout << "jugador: " << (it->second).getPlayerId() << "derrotado------" << std::endl;
	}
	return i;
	/*
	for (auto it = players_info.begin(); it != players_info.end(); ++it){
		int i = (it->second).checkVictoryConditions();
		if (i == DEFEAT){
			std::cout << "jugador: " << (it->second).getPlayerId() << "derrotado------" << std::endl;
		}
	}
	*/
}

int infoPlayers::getPlayerTechLevel(int id_p){
	std::map<int,infoPlayer>::iterator it;
	it = players_info.find(id_p);
	return (it->second).getCurrentTechLvl();
}

void infoPlayers::incrementUnitsCount(int id_p){
	std::map<int,infoPlayer>::iterator it;
	it = players_info.find(id_p);
	(it->second).incrementUnitsCount();
}

void infoPlayers::decrementUnitsCount(int id_p){
	std::map<int,infoPlayer>::iterator it;
	it = players_info.find(id_p);
	(it->second).decrementUnitsCount();
}

///////////////////////////////////////////////////////////////////////////////


		
infoPlayer::infoPlayer(int id, std::vector<int> allies): player_id(id), 
allies(allies), current_tech_lvl(1), state(OK){}

infoPlayer::infoPlayer(int id): player_id(id), current_tech_lvl(1){}

int infoPlayer::getPlayerId(){
	return player_id;
}

int infoPlayer::getCurrentTechLvl(){
	return current_tech_lvl;
}

void infoPlayer::incrementTechLvl(){
	current_tech_lvl++;
}

void infoPlayer::decrementTechLvl(){
	current_tech_lvl--;
}

void infoPlayer::getAllies(std::vector<int> &a){
	a = allies;
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

int infoPlayer::checkVictoryConditions(){
	if ((units_count == 0 || !this->fortAlive())) {
		state = DEFEAT;
		return DEFEAT;
	}
	return OK;
}