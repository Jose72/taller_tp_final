#include "infoGame.h"
#include <map>
#include <iostream>
#include "team.h"
		
		
infoGame::infoGame(int max_p, int game_type, int teams){
	this->max_players = max_p;
	this->game_type = game_type;
	this->max_teams = teams;
	if (game_type == DEATHMATCH){
		this->max_teams = max_p;
	}
	this->initializeTeams();
}	
	


void infoGame::initializeTeams(){
		unsigned int team_limit = 0;
		//si es un deathmatch hay tantos equipos como jugadores
		if (game_type == DEATHMATCH){
			team_limit = max_players;
		} else {
			team_limit = max_teams;
		}
		for (unsigned int i = 1; i <= team_limit; ++i){
			team t(i, max_players/max_teams);
			teams.push_back(t);
		}
	}

int infoGame::addNewPlayer(int id_p, serverProtocol *prot, int team_n){
	if (game_type == DEATHMATCH){
		//meto en el primero libre
		for (auto it = teams.begin(); it != teams.end(); ++it){
			if (!it->isFull()){
				it->addPlayer(id_p, prot);
				return 0;
			}
		}
	} else{
		//busco team con el id, si no esta lleno meto al jugador
		for (auto it = teams.begin(); it != teams.end(); ++it){
			if (it->getTeamNumber() == team_n){
				if (!it->isFull()){
					it->addPlayer(id_p, prot);
					return 0;
				}
			}
		}
	}
	return -1;
}

//devuelde DEFEAT si el equipo fue derrotado en este turno
//OK si sigue vivo
//-1 si ya estaba derrotado
int infoGame::updateVictoryCond(int team_n){
	//recorro buscando el team
	for (auto it = teams.begin(); it != teams.end(); ++it){
		if (team_n == it->getTeamNumber()){
			if (it->isDefeated()) return -1;
			int i = it->updateVictoryConditions();
			return i;
		}
	}
	return -2;
}

//si un jugador llego a su limite de poblacion
bool infoGame::maxPopReached(int team_n){
	for (auto it = teams.begin(); it != teams.end(); ++it){
		if (team_n == it->getTeamNumber()){
			return it->maxUnitsReached();
		}
	}
	return false;
}

void infoGame::setFort(int team_n, unit* f){
	for (auto it = teams.begin(); it != teams.end(); ++it){
		if (team_n == it->getTeamNumber()){
			it->setFort(f);
		}
	}
}

void infoGame::incrementUnitsCount(int team_n){
	for (auto it = teams.begin(); it != teams.end(); ++it){
		if (team_n == it->getTeamNumber()){
			it->incrementUnitsCount();
		}
	}
}

void infoGame::decrementUnitsCount(int team_n){
	for (auto it = teams.begin(); it != teams.end(); ++it){
		if (team_n == it->getTeamNumber()){
			it->decrementUnitsCount();
		}
	}
}

int infoGame::getCapturedTer(int team_n){
	for (auto it = teams.begin(); it != teams.end(); ++it){
		if (team_n == it->getTeamNumber()){
			return it->getCapturedTer();
		}
	}
	return 0;
}

void infoGame::initializeTeam(int team_n, unit* fort, int unit_count){
	for (auto it = teams.begin(); it != teams.end(); ++it){
		if (team_n == it->getTeamNumber()){
			it->initialize(fort, unit_count);
		}
	}
}

int infoGame::checkForWinner(){
	int defeated_count = 0;
	int winner = NO_WINNER;
	for (auto it = teams.begin(); it !=teams.end(); ++it){
		if (it->isDefeated()){
			defeated_count++;
		} else {
			winner = it->getTeamNumber();
		}
	}
	//si solo quedo uno no derrotado es el ganador
	if (defeated_count == (int)max_teams - 1){
		return winner;
	} 
	return NO_WINNER;
}

void infoGame::updateCapturedTer(int old_owner, int new_owner){
	for (auto it = teams.begin(); it != teams.end(); ++it){
		if (new_owner == it->getTeamNumber()){
			it->incrementCapturedTer();
		}
		if (old_owner == it->getTeamNumber()){
			it->decrementCapturedTer();
		}
	}
}

void infoGame::sendTeamNumbers(){
	for (auto it = teams.begin(); it != teams.end(); ++it){
		it->sendTeamNumber();
	}
}

bool infoGame::teamDefeated(int team_n){
	for (auto it = teams.begin(); it != teams.end(); ++it){
		if (team_n == it->getTeamNumber()){
			return it->isDefeated();
		}
	}
	return false;
}

void infoGame::initializeTeamsData(std::map<int, unit*> &units){
	for (auto it = units.begin(); it != units.end(); ++it){
		unit *u = it->second;
		int team_n = u->getOwner();
		//si es un fuerte lo seteo
		if (u->getUnitId() == FORT){
			this->setFort(team_n, u);
		}
		//si es un robot(unidad) aumento el contador
		if (u->getClassId() == ROBOT){
			this->incrementUnitsCount(team_n);
		}
	}
}

void  infoGame::sendInitialPos(){
	for (auto it = teams.begin(); it != teams.end(); ++it){
		it->sendInitialPos();
	}
}