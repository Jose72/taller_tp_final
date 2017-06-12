#include "infoPlayer.h"
#include <map>
#include <iostream>
		
		
infoPlayers::infoPlayers(int max_p, int game_type, int teams){
	max_players = max_p;
	game_type = game_type;
	teams_count = teams;
}	
		
//adhiere nuevo jugador, con su protocolo
void infoPlayers::addNewPlayer(int id_p, serverProtocol *prot){
	if (players_info.size() < max_players){
		infoPlayer i(id_p, prot);
		players_info.insert(std::pair<int,infoPlayer>(id_p,i));
	}
}


//no usar!!
void infoPlayers::addNewPlayer(int id_p){
	if (players_info.size() < max_players){
		infoPlayer i(id_p);
		players_info.insert(std::pair<int,infoPlayer>(id_p,i));
	}
}


//actualiza los tech level correspondientes ante una captura de bandera
void infoPlayers::updateTechLevels(int id_old, int id_new){
	std::map<int,infoPlayer>::iterator it;
	std::map<int,infoPlayer>::iterator it2;
	it = players_info.find(id_old);
	if (id_old == it->first){
		(it->second).decrementTechLvl();
		}
	it2 = players_info.find(id_new);
		if (id_old == it2->first){
			std::cout << "n t: " << (it2->second).getCurrentTechLvl() << std::endl;
			(it->second).incrementTechLvl();
			std::cout << "n t: " << (it2->second).getCurrentTechLvl() << std::endl;
		}
}

//inciiaiza a un jugador
//guarda el puntero al fuerte y la cant de unidades iniciales
void infoPlayers::initializePlayer(int id_p, unit *fort, int units_count){
	std::map<int,infoPlayer>::iterator it;
	it = players_info.find(id_p);
	if (id_p == it->first)
		(it->second).initialize(fort, units_count);
}


//devuelde DEFEAT si el jugador fue derrotado en este turno
//OK si sigue vivo
//-1 si ya estaba derrotado
int infoPlayers::updateVictoryConditions(int id_p){
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
int infoPlayers::checkForWinner(){
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


//envio a los jugadores su tech level actual
void infoPlayers::sendUpdateTechLvl(){
	for (auto it = players_info.begin(); it != players_info.end(); ++it){
		(it->second).sendUpdateTechLvl();
	}
}

//si un jugador llego a su limite de poblacion
bool infoPlayers::maxPopulationReached(int id_p){
	std::map<int,infoPlayer>::iterator it;
	it = players_info.find(id_p);
	if (id_p == it->first){
		return (it->second).maxUnitsReached();
	} 
	return false;
}

///////////////////////////////////////////////////////////////////////////////




infoPlayer::infoPlayer(int id, serverProtocol *prot): player_id(id), prot(prot), current_tech_lvl(1){}

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

void infoPlayer::sendUpdateTechLvl(){
	prot->sendUpdateTechLvl(current_tech_lvl);
}

bool infoPlayer::isDefeated(){
	return (state == DEFEAT);
}