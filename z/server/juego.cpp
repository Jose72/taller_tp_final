#include "juego.h"
#include <vector>
#include "gameMap.h"
#include <map>
#include <set>
#include <iostream>
#include "actualizeUnit.h"
#include <unistd.h>
#include "unitBuilder.h"
#include "infoUnits.h"
#include "deathHandler.h"
#include "infoPlayer.h"
#include <ctime>
#include "Protocol.h"
#include "JsonHandler.h"
#include "defeatHandler.h"
#include "JsonUnitInfoHandler.h"


#define MILISEC_SLICE 100

//cant jugadores
//tipo de juego(deathmatch o equipos)
//cant equipos
juego::juego(int creator, int cant_players, int game_t, int cant_teams, std::string &map_name, 
std::string &map_folder, std::string &unit_info_path): 
id_creator(creator), map_name(map_name), max_players(cant_players), teams(cant_teams), 
game_type(game_t), map_folder(map_folder), u_info(unit_info_path), builder(u_info), id_unit_counter(1), 
g_info(infoGame(cant_players, game_t, cant_teams)), stop_signal(false), started(false), 
running(false) {}

void juego::getDescription(int &creat, int &max_p, int &cant_p, int &game_t, int &cant_t){
    tLock l(game_m);
	creat = id_creator;
	max_p = max_players;
	cant_p = cli_skts.size();
	game_t = game_type;
	cant_t = teams;
	
}

bool juego::isFull(){
	return ((unsigned int)max_players == cli_skts.size());
}

bool juego::isCreator(int c){
	return (id_creator == c);
}

bool juego::gameStarted(){
	return started;
}

//si empezo y termino de correr
bool juego::readyToClean(){
	return (started && !running);
}

int juego::checkVictory(){
	//para cada cliente
	for (int i = 1; i <= teams; ++i){
		if (DEFEAT == g_info.updateVictoryCond(i)){
			defeatHandler df;
			//si fue derrotado, hay que ver que hacer con las unidades
			//team en vez de player
			//std::cout << "DEFEAT: " << i << std::endl;
			df.defeatPlayer(i, units);
		}
		//me fijo si hay ganador
		int winner = g_info.checkForWinner();
		if (winner != NO_WINNER){
			//std::cout << "WINNER: " << winner << std::endl;
			for (auto it = protocols.begin(); it != protocols.end(); ++it){
				//hay que enviarles a todos que termino la partida
				(*it)->sendVictory(winner);
			}
			return winner;
		}	
	}
	return NO_WINNER;
}

void juego::stop(){
	std::cout << "juego stop" << std::endl;	
	//rompo los sockets
	stop_signal = true;
	for (auto it = cli_skts.begin(); it != cli_skts.end(); ++it){
			(*it)->shutdown(SHUT_WR);
	}
	std::cout << "juego stop out" << std::endl;	
}

void juego::unit_cleaner(){
	deathHandler death_h(builder);
	for (auto it = units.begin(); it != units.end(); ){
		unit *u = it->second;
		bool not_edificio = (u->getClassId() != BUILDING);
		int estado = u->getState();
		switch(estado){
			case(DEAD):{
				death_h.death(*u, units, id_unit_counter, mapa, g_info);//handler por si tiene q hacer algo
				//si no es un edificio lo elimino
				if (not_edificio){
					delete it->second;
					it = units.erase(it); // borro de la lista
				} else {
					++it;
				}
				break;
			}
			case(ERASED):{
				it->second->stopFollowers();
				delete it->second;
				it = units.erase(it);
				break;
			}
			default:{
				++it;
				break;
			}
			
		}
	}
}

void juego::take_event(Event &e){
	tLock l(event_m);//lockeo
	//std::cout << "event push" << std::endl;
	event_list.push(e);
	return;
}

bool juego::readyToStart(){
	//si tengo tantos clientes como jugadores espero
	if (cli_skts.size() == (unsigned int) max_players) return true;
	return false;
}

int juego::clientJoin(int cli_id, tSocket *cli_s, int team_n){
	tLock l(game_m);
	if (cli_skts.size() < (unsigned int) max_players){
		serverProtocol *p = new serverProtocol(*cli_s);
		int res = g_info.addNewPlayer(cli_id, p, team_n);
		if (res == 0){
			cli_skts.push_back(cli_s);
			protocols.push_back(p);
			cli_ids.push_back(cli_id);
		}
		return res;
	}
	return 1;
}

void juego::sendInit(){
	//map_name = "map";
	JsonHandler jsonHandler(map_folder);
	std::vector<int> mapDes = jsonHandler.jsonToMap(map_name);
	mapa = gameMap(mapDes);
    jsonHandler.jsonToUnits(id_unit_counter,builder,units,map_name);


	
	
	//hay que inicilizar la info de cada equipo
	//codigo de equipo (owner), puntero a fuerte, cant incial de unidades
	//cant de unidades es solo robots y vehiculos, edificios no cuentan
	//un solo fuerte por equipo
	g_info.initializeTeamsData(units);
	
	//inicializaciond e lso territorios
	for (auto it = units.begin(); it != units.end(); ++it){
		unit *u = it->second;
		if (u->getUnitId() == FLAG){
			auto it2 = it;
			it2++;
			territory t(u, (it2->second));
			territorios.push_back(t);
		}
	}
	
	//inicializacion de los vehiculos
	//hay que crearles un conductor y agregarlo al mapa de unidades (grunt por defecto)
	for (auto it = units.begin(); it != units.end(); ++it){
		unit *u = it->second;
		if (VEHICLE == u->getClassId() && u->getOwner() != 0){
			unit *driv = builder.build(GRUNT, u->getOwner(), u->getX(), u->getY());
			driv->instantDrive(u);
			units.insert(std::pair<int,unit*>(id_unit_counter, driv));
			id_unit_counter++;//incremento id_unit
			g_info.incrementUnitsCount(u->getOwner());
		}
	}


	//seteo en el mapa las casillas bloqueadas (o desbloqueadas por unidades)
	mapa.setBlocking(units);
	
	
	////////////////////////////////
	//ENVIAR NUMERO DE EQUIPO ANTES QUE TODO
	g_info.sendTeamNumbers();
	
	///////////////////////////////
	//envio la dimension del mapa
	int dim_m = jsonHandler.getMapDimension(map_name);
	for (auto it = protocols.begin(); it != protocols.end(); ++it){
		(*it)->send_map_dim(dim_m);
	}
	
	//envio pos inicial
	g_info.sendInitialPos();
	
	//envio el mapa y las unidades iniciales a todos lo jugadores
	for (auto it = protocols.begin(); it != protocols.end(); ++it){
		(*it)->send_map(mapDes);
		(*it)->send_units_game(units);
	}
}


void juego::eventHandle(Event &e, std::map<int,unit*> &units){
	std::map<int,unit*>::iterator it;
	it = units.find(e.getUnitId());
	
	if (it->first != e.getUnitId()) return; //no encontro a la unidad
	
	int st = it->second->getState();
	if (st == DRIVING || st == DEAD) return; //si esta muerta o onduciendo no puede 
		
	//el equipo fue derrotado
	if (g_info.teamDefeated(it->second->getOwner())) return;
	
	switch (e.getOpCode()){
		case 0:
			{
			//moverse
			//solo robots o vehiculos
			//std::cout << "move order" << std::endl;
            //std::cout << "move u: " << it->first << " x: " << e.getX() << " y: " << e.getY() << std::endl;
			if ((it->second)->getClassId() == ROBOT || (it->second)->getClassId() == VEHICLE) {
				(it->second)->move(e.getX(),e.getY());
			}
			}
			return;
			
		case 1:
			{
			//ataque
            //std::cout << "ataq order" << std::endl;
			std::map<int,unit*>::iterator it2;
			it2 = units.find(e.getX());
			int unit_uniq_code = it2->first;
			if (unit_uniq_code != e.getX()) return; //no encontro a la unidad
			unit *target = it2->second;
			//solo robots o vehiculos
			if (((it->second)->getClassId() == ROBOT) || ((it->second)->getClassId() == VEHICLE)) {
				if ((target->getUnitId() != FLAG) 
				&& (target->getUnitId() != BULLET) 
				&& !(target->getClassId() == VEHICLE && target->getOwner() == 0)){
					(it->second)->attack(target);
				} else {
					//si la unidad no es atacable
				}
			} 
			}
			return;
		case 2: 
			{
			//crear
            //std::cout << "create order: " << e.getX() << std::endl;
			int u_to_create = e.getX();
			(it->second)->create(u_to_create, (u_info.getFabTime(u_to_create) / 10));
			return;
			}
		case 3: //conducir
			{
			//busco la unidad destino
			//si no es robot salgo
			if (it->second->getClassId() != ROBOT) return;
			std::map<int,unit*>::iterator it2;
			it2 = units.find(e.getX());
			if (it2->first != e.getX()) return; //no encontro a la unidad
			(it->second)->drive(it2->second);
			return;
			}
	}
}

void juego::run(){
	started = true;
	running = true;
	
	//espero a que el juego este listo
	while(!this->readyToStart() && !stop_signal){
		usleep(500000);
	}
	//envio confirmacion a los clientes apra que empiezen a recibir
	for (auto it = protocols.begin(); it != protocols.end(); ++it){
		(*it)->sendOKConfimation();
	}
	//envio de mapa, unidades iniciales y cosas basicas
	this->sendInit();
	
	//seteo el actualizador de unidades
	actualizeUnit actualizer(builder, u_info);
	
	//bucle leo eventos, ejecuto y envio cambios a jugadores
	int s = 1;
	while(s > 0 && !stop_signal && running){
			//tomo tiempo
			clock_t Start = clock();
			
            int c = event_list.size();
			int i = 0;
            while (!event_list.empty() && i < c) {
				//lockeo cola de evntos
                event_m.lock();
                Event e = event_list.front();
                event_list.pop();
                event_m.unlock();
				//deslockeo
                eventHandle(e, units);
                i++;
            }

			//actualizo las undiades
			for (auto it = units.begin(); it != units.end(); ++it){
				unit *u = it->second;
				actualizer(it->first, *u, units, mapa, MILISEC_SLICE, id_unit_counter, g_info);
			}
			
			//actualzicion de territorios
			for (auto it = territorios.begin(); it != territorios.end(); ++it){
				it->changeOwnership();
			}
			
			//envio actualizacion de las unidades
			s = 0;
            for (auto it = protocols.begin(); it != protocols.end(); ++it){
                 s += (*it)->sendActualization(units);
            }
			
			//limpio los fiambres
			unit_cleaner();
			
			//check si gano alguien, o si perdio
			if (NO_WINNER != checkVictory()){
				//si hubo ganador envio una ultima actualizacion de unidades
				for (auto it = protocols.begin(); it != protocols.end(); ++it){
					(*it)->sendActualization(units);
				}
				running = false;
			}
			
			
		int elapsed_time = (clock() - Start) * 1000000 / CLOCKS_PER_SEC;
		int sleep_time = (MILISEC_SLICE * 1000) - elapsed_time;
		if (sleep_time < 0) sleep_time = 0;
		//std::cout << "Time Difference: " << sleep_time << std::endl;
		usleep(sleep_time);
			
	}
	
	//por si salio por otras razones
	running = false;
	
	//limpio unidades al final del juego
	//std::cout << "delete units" << std::endl;
	for (auto it = units.begin(); it != units.end(); ++it){
		delete it->second;
	}
	
	//y los protocolos
	for (auto it = protocols.begin(); it != protocols.end(); ++it){
		delete (*it);
	}
	
	//std::cout << "juego out" << std::endl;	
	return;
}
