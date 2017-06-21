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
	
/*
	
//adhiere nuevo jugador, con su protocolo
void infoGame::addNewPlayer(int id_p, serverProtocol *prot){
	if (players_info.size() < max_players){
		infoPlayer i(id_p, prot);
		players_info.insert(std::pair<int,infoPlayer>(id_p,i));
	}
}


//no usar!!
void infoGame::addNewPlayer(int id_p){
	if (players_info.size() < max_players){
		infoPlayer i(id_p);
		players_info.insert(std::pair<int,infoPlayer>(id_p,i));
	}
}



//inciiaiza a un jugador
//guarda el puntero al fuerte y la cant de unidades iniciales
void infoGame::initializePlayer(int id_p, unit *fort, int units_count){
	std::map<int,infoPlayer>::iterator it;
	it = players_info.find(id_p);
	if (id_p == it->first)
		(it->second).initialize(fort, units_count);
}


//devuelde DEFEAT si el jugador fue derrotado en este turno
//OK si sigue vivo
//-1 si ya estaba derrotado
int infoGame::updateVictoryConditions(int id_p){
	//busco el info del player
	std::map<int,infoPlayer>::iterator it;
	it = players_info.find(id_p);
	//si no fue derrotado, hago el update
	if ((it->second).isDefeated()) return -1;
	int i = (it->second).updateVictoryConditions();
	if (i == DEFEAT){
			std::cout << "jugador: " << (it->second).getPlayerId()
			<< "derrotado------" << std::endl;
	}
	//devuelvo el resultado
	return i;
}


//retorna el id del winner si lo hay, sino retorna 0
int infoGame::checkForWinner(){
	//si es un deathmath
	if (game_type == DEATHMATCH){
		int defeated_count = 0;
		int winner = NO_WINNER;
		//me fijo que en los jugadores
		for (auto it = players_info.begin(); it != players_info.end(); ++it){
			if ((it->second).isDefeated()){
				defeated_count++;
			} else {
				winner = (it->second).getPlayerId();
			}
		}
		//si solo quedo uno no derrotado es el ganador
		if (defeated_count == (int)max_players - 1){
			return winner;
		} 
		return NO_WINNER;
	}
	return NO_WINNER;
}



void infoGame::incrementUnitsCount(int id_p){
	std::map<int,infoPlayer>::iterator it;
	it = players_info.find(id_p);
	(it->second).incrementUnitsCount();
}

void infoGame::decrementUnitsCount(int id_p){
	std::map<int,infoPlayer>::iterator it;
	it = players_info.find(id_p);
	(it->second).decrementUnitsCount();
}


//si un jugador llego a su limite de poblacion
bool infoGame::maxPopulationReached(int id_p){
	std::map<int,infoPlayer>::iterator it;
	it = players_info.find(id_p);
	if (id_p == it->first){
		return (it->second).maxUnitsReached();
	} 
	return false;
}
*/
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


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
			std::cout << "team: " << i << std::endl;
			std::cout << "ppt: " << max_players/max_teams << std::endl;
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
		for (auto it = teams.begin(); it != teams.end(); ++it){
			if (!it->isFull()){
				it->addPlayer(id_p, prot);
				return 0;
			}
		}
		/*
		//busco team con el id, si no esta lleno meto al jugador
		for (auto it = teams.begin(); it != teams.end(); ++it){
			if (it->getTeamNumber() == team_n){
				if (!it->isFull()){
					it->addPlayer(id_p, prot);
					return 0;
				}
			}
		}
		*/
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
			if (i == DEFEAT){
				std::cout << "team: " << it->getTeamNumber()
				<< "derrotado------" << std::endl;
			}
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

void infoGame::initializeTeam(int team_n, std::vector<unit*> forts, int unit_count){
	for (auto it = teams.begin(); it != teams.end(); ++it){
		if (team_n == it->getTeamNumber()){
			it->initialize(forts, unit_count);
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