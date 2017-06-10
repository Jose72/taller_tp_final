#include "juego.h"
#include <vector>
#include "gameMap.h"
#include <map>
#include <set>
#include <iostream>
#include "actualizeUnit.h"
#include <unistd.h>
#include "unitBuilder.h"
#include "deathHandler.h"
#include "infoPlayer.h"

#include "Protocol.h"

//cant jugadores
//tipo de juego(deathmatch o equipos)
//cant equipos
juego::juego(int cant_players, int game_t, int cant_teams): 
max_players(cant_players), p_info(infoPlayers(cant_players, 
game_t, cant_teams)), running(false) {
	id_unit_counter = 1; //se empieza contando desde 1
}

bool juego::isRunning(){
	return running;
}

void juego::checkVictory(){
	//p_info.checkVictoryConditions();
}

void juego::stop(){
	std::cout << "juego stop" << std::endl;	
	
	//rompo los sockets
	for (auto it = cli_skts.begin(); it != cli_skts.end(); ++it){
			(*it)->shutdown(SHUT_WR);
	}
	
	std::cout << "juego stop out" << std::endl;	
	
}

void juego::take_event(Event &e){
	tLock l(game_m);//lockeo
	std::cout << "event push" << std::endl;
	event_list.push(e);
	return;
}

bool juego::readyToStart(){
	//si tengo tantos clientes como jugadores espero
	if (cli_skts.size() == (unsigned int) max_players) return true;
	return false;
}

int juego::clientJoin(int cli_id, tSocket *cli_s){
	if (cli_skts.size() < (unsigned int) max_players){
		cli_skts.push_back(cli_s);
		
		// protocolos
		protocols.push_back(serverProtocol(*cli_s));
		players_info.push_back(infoPlayer(cli_id));
		
		p_info.addNewPlayer(cli_id);
		return 0;
	}
	return 1;
}

void juego::sendInit(){
	int map_codes[100] = {0};
	map_codes[15] = 1;
	map_codes[16] = 1;
	map_codes[17] = 1;
	map_codes[18] = 1;
	map_codes[31] = 1;
	map_codes[32] = 1;
	map_codes[33] = 1;
	map_codes[34] = 1;
	map_codes[43] = 2;
	map_codes[44] = 2;
	map_codes[45] = 2;
	map_codes[46] = 2;
	map_codes[47] = 2;
	map_codes[48] = 2;
	map_codes[53] = 2;
	map_codes[54] = 2;
	map_codes[55] = 2;
	map_codes[56] = 2;
	map_codes[57] = 2;
	map_codes[58] = 2;

	int sss = 100;
	
	//cargo mi mapa
	mapa = gameMap(map_codes, sss);
	
	
	//unit* u1 = new unit(1, GRUNT, 60, 15);
	unit *u1 = builder.build(GRUNT, 1, 60, 15);
	units.insert(std::pair<int,unit*>((units.size()+1),u1));
	id_unit_counter++;

	unit *u2 = builder.build(GRUNT, 2, 160, 15);
	units.insert(std::pair<int,unit*>((units.size()+1),u2));
	id_unit_counter++;

	

	//protocol
	for (auto it = protocols.begin(); it != protocols.end(); ++it){
		it->send_map((int*)&map_codes,100);
		it->send_units_game(units);
	}

	
	
	
	
}


void juego::eventHandle(Event &e, std::map<int,unit*> &units){
	std::map<int,unit*>::iterator it;
	it = units.find(e.getUnitId());
	
	if (it->first != e.getUnitId()) return; //no encontro a la unidad
	
	switch (e.getOpCode()){
		case 0:
			//moverse
			//solo robots o vehiculos
			
			//if ((it->second)->getClassId() == ROBOT || (it->second)->getClassId() == VEHICLE) {
			(it->second)->move(e.getX(),e.getY());
			//}
			return;
			
		case 1:
			//ataque
			//moverse
			std::map<int,unit*>::iterator it2;
			it2 = units.find(e.getX());
			
			if (it2->first != e.getX()) return; //no encontro a la unidad
			
			//solo robots o vehiculos
			//if ((it->second)->getClassId() == ROBOT || (it->second)->getClassId() == VEHICLE) {
			(it->second)->attack(it2->second);
			//}
			return;
		/*
		case 2: //crear
			(it->second)->create(e.getX());
			return;
		case 3: //conducir
			//busco la unidad destino
			std::map<int,unit*>::iterator it2;
			it2 = units.find(e.getX());
			if (it2->first != e.getX()) return; //no encontro a la unidad
			(it->second)->drive(it2->second);
			return;
			
		*/
	}
}

void juego::run(){
	
	running = true;
	//mapa codes de las casillas
	
	actualizeUnit actualizer;
	deathHandler death_h;
	
	
	//bucle leo eventos, ejecuto y envio cambios a jugadores
	int s = 1;
	while(s > 0){
			//std::cout << "loop juego" << std::endl;
			//lockeo cola de evntos
			game_m.lock();
			if (!event_list.empty()){
				Event e = event_list.front();
				event_list.pop();
				
				/*
				//esto esta harcodeado, tendria que llamar a una funcion
				//que identifique la op y ejecute (handler)
				std::map<int,unit*>::iterator it;
				it = units.find(e.getId());
				//find devuelte el iterador del elemento 
				//o el ultimo si no existe la key
				//hay que chequear que devolvio correctamente
				if (it->first == e.getId()){
					unit *u1 = it->second;
					eventHandle()
					u1->move(e.getX(), e.getY()); //hay que hacer un handler
				}
				*/
				
				eventHandle(e, units);
			}
			//deslockeo
			game_m.unlock();
			
			
			//actualizo las undiades (pendiente: crear una func aparte)
			std::set<int> dead_units;
			std::set<int> actualized_units;
			for (auto it = units.begin(); it != units.end(); ++it){
				unit *u = it->second;
				actualizer(it->first, *u, units, mapa, 200, id_unit_counter, dead_units, actualized_units);
			}
			
			usleep(200000);
			
            for (auto it = protocols.begin(); it != protocols.end(); ++it){
                 s = it->sendActualization(units);
            }
			
			//limpio los fiambres
			//std::cout << "units clean " << std::endl;
			for (auto it = units.begin(); it != units.end(); ){
				unit *u = it->second;
				if (u->isDead()) {
					death_h.death(*u, units);//handler por si tiene q hacer algo
					std::cout << "unit " << it->first << " dead" << std::endl;
					delete it->second; // libero mem
					it = units.erase(it); // borro de la lista
				} else {
					++it;
				}
				
			}
			
	}
	
	
	std::cout << "delete units" << std::endl;
	for (auto it = units.begin(); it != units.end(); ++it){
		delete it->second;
	}
	

	std::cout << "juego out" << std::endl;	
	
	
	return;
}