#include "team.h"
#include <iostream>

team::team(int team_n, int max_p): team_n(team_n), max_p(max_p){
	this->max_units = 50 * max_p;
	this->unit_count = 0;
	this->state = OK;
	this->captured_territories = max_p;
	this->fort = nullptr;
}

int team::addPlayer(int p_id, serverProtocol *prot){
	infoPlayer ip(p_id, prot);
	players.push_back(ip);
	return 0;
}

int team::getTeamNumber(){
	return team_n;
}

void team::setFort(unit *f){
	this->fort = f;
}

bool team::isFull(){
	return (max_p == players.size());
}


bool team::isDefeated(){
	return (state == DEFEAT);
}

bool team::fortIsAlive(){
	return (fort->isAlive());
}

int team::updateVictoryConditions(){
	//std::cout << "team: " << team_n << " u: " << unit_count << " fa: " << this->fortsAlive() << std::endl;
	if ((unit_count == 0 || !this->fortIsAlive())) {
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

void team::initialize(unit* fort, int unit_count){
	this->fort = fort;
	this->unit_count = unit_count;
}

void team::incrementCapturedTer(){
	captured_territories++;
}

void team::decrementCapturedTer(){
	captured_territories--;
}

void team::sendTeamNumber(){
	for (auto it = players.begin(); it != players.end(); ++it){
		it->sendTeamNumber(team_n);
	}
}

void team::sendInitialPos(){
	for (auto it = players.begin(); it != players.end(); ++it){
		it->sendInitialPos(fort->getX(), fort->getY());
	}
}