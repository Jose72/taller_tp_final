#include "team.h"
#include <iostream>

team::team(int team_n, int max_p): team_n(team_n), max_p(max_p){
	max_units = 50 * max_p;
	unit_count = 0;
	state = OK;
	captured_territories = max_p;
}

int team::addPlayer(int p_id, serverProtocol *prot){
	infoPlayer ip(p_id, prot);
	players.push_back(ip);
	return 0;
}

int team::getTeamNumber(){
	return team_n;
}

bool team::isFull(){
	return (max_p == players.size());
}


bool team::isDefeated(){
	return (state == DEFEAT);
}

bool team::fortsAlive(){
	int c = 0;
	for (auto it = forts.begin(); it != forts.end(); ++it){
		if ((*it)->isAlive()){
			c++;
		}
	}
	std::cout << "c: " << c << std::endl;
	return (c > 0);
}

int team::updateVictoryConditions(){
	if ((unit_count == 0 || !this->fortsAlive())) {
		std::cout << "zxxxxxx: " << unit_count << std::endl;
		state = DEFEAT;
		return DEFEAT;
	}
	return OK;
}

bool team::maxUnitsReached(){
	return (unit_count >= max_units);
}

void team::incrementUnitsCount(){
	unit_count++;
}

void team::decrementUnitsCount(){
	unit_count--;
}

int team::getCapturedTer(){
	return captured_territories;
}

void team::initialize(std::vector<unit*> forts, int unit_count){
	this->forts = forts;
	this->unit_count = unit_count;
}

void team::incrementCapturedTer(){
	captured_territories++;
}

void team::decrementCapturedTer(){
	captured_territories--;
}
