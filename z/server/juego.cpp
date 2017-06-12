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
#include <ctime>
#include "Protocol.h"

//cant jugadores
//tipo de juego(deathmatch o equipos)
//cant equipos
juego::juego(int creator, int cant_players, int game_t, int cant_teams): 
id_creator(creator), max_players(cant_players), teams(cant_teams), 
game_type(game_t), p_info(infoPlayers(cant_players, 
game_t, cant_teams)), running(false) {
	id_unit_counter = 1; //se empieza contando desde 1
	team_count = 1;
}

bool juego::isRunning(){
	return running;
}

void juego::getDescription(int &creat, int &max_p, int &cant_p, int &game_t, int &cant_t){
    tLock l(game_m);
	creat = id_creator;
	max_p = max_players;
	cant_p = cli_skts.size();
	game_t = game_type;
	cant_t = teams;
	
}

bool juego::isCreator(int c){
	if (id_creator == c) return true;
	return false;
}

int juego::checkVictory(){
	//para cada cliente
	for (auto it = cli_ids.begin(); it != cli_ids.end(); ++it){
		if (DEFEAT == p_info.updateVictoryConditions(*it)){
			//si fue derrotado, busco sus unidades y las seteo en DEFEATED
			for (auto it2 = units.begin(); it2 != units.end(); ++it2){
				unit *u = (it2->second);
				if (u->getOwner() == (*it)){
					u->changeState(DEFEATED);
				}
			}
		}
	}
	//me fijo si hay ganador
	int winner = p_info.checkForWinner();
	if (winner != NO_WINNER){
		std::cout << "winner: " << winner<< std::endl;
		//p_info.sendVictoryMessages(winner);
		//hay que enviarles a todos que termino la partida
	}
	return winner;
}

void juego::stop(){
	std::cout << "juego stop" << std::endl;	
	
	//rompo los sockets
	for (auto it = cli_skts.begin(); it != cli_skts.end(); ++it){
			(*it)->shutdown(SHUT_WR);
	}
	
	std::cout << "juego stop out" << std::endl;	
	
}

void juego::unit_cleaner(){
	deathHandler death_h;
	for (auto it = units.begin(); it != units.end(); ){
		unit *u = it->second;
		bool edificio = (u->getClassId() != BUILDING);
		if (u->isDead()) {
			death_h.death(*u, units);//handler por si tiene q hacer algo
			//si no es un edificio lo elimino
			if (edificio){
				p_info.decrementUnitsCount(u->getOwner()); //decremento cant unidadades player
				delete it->second; // libero mem
				it = units.erase(it); // borro de la lista
				
			}
		} else {
			++it;
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

int juego::clientJoin(int cli_id, tSocket *cli_s){
	tLock l(game_m);
	if (cli_skts.size() < (unsigned int) max_players){
		cli_skts.push_back(cli_s);
		
		// protocolos
		serverProtocol *p = new serverProtocol(*cli_s);
		protocols.push_back(p);
		
		cli_ids.push_back(cli_id);
		p_info.addNewPlayer(cli_id, p);
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
	unit *u1 = builder.build(GRUNT, 1, 15, 15);
	units.insert(std::pair<int,unit*>((id_unit_counter+1),u1));
	id_unit_counter++;

	unit *u2 = builder.build(FLAG, 200, 15);
	units.insert(std::pair<int,unit*>((id_unit_counter+1),u2));
	id_unit_counter++;

	unit *u3 = builder.build(FORT, 1, 40, 40);
	units.insert(std::pair<int,unit*>((id_unit_counter+1),u3));
	id_unit_counter++;

	unit *u4 = builder.build(GRUNT ,2,280, 280);
	units.insert(std::pair<int,unit*>((id_unit_counter+1),u4));
	id_unit_counter++;
	
	
	//hay que inicilizar la info de cada jugador
	//codigo de juagdor (owner), puntero a fuerte, cant incial de unidades
	//cant de unidades es solo robots y vehiculos, edificios no cuentan
	p_info.initializePlayer(1, u3, 1);
	p_info.initializePlayer(2, nullptr, 1);

	//protocol
	for (auto it = protocols.begin(); it != protocols.end(); ++it){
		(*it)->send_map((int*)&map_codes,sss);
		(*it)->send_units_game(units);
	}


}


void juego::eventHandle(Event &e, std::map<int,unit*> &units){
	std::map<int,unit*>::iterator it;
	it = units.find(e.getUnitId());
	
	if (it->first != e.getUnitId()) return; //no encontro a la unidad
	
	switch (e.getOpCode()){
		case 0:
			{
			//moverse
			//solo robots o vehiculos
			std::cout << "move order" << std::endl;
            std::cout << "move u: " << it->first << " x: " << e.getX() << " y: " << e.getY() << std::endl;
			if ((it->second)->getClassId() == ROBOT || (it->second)->getClassId() == VEHICLE) {
				(it->second)->move(e.getX(),e.getY());
			}
			
			}
			return;
			
		case 1:
			{
			//ataque
            std::cout << "ataq order" << std::endl;
			//moverse
			std::map<int,unit*>::iterator it2;
			it2 = units.find(e.getX());
			int class_target = it2->first;
			if (class_target != e.getX()) return; //no encontro a la unidad
			
			//solo robots o vehiculos
			if (((it->second)->getClassId() == ROBOT || (it->second)->getClassId() == VEHICLE) && 
			class_target != FLAG) {
				(it->second)->attack(it2->second);
				}
			}
			return;
		
		case 2: 
			{
			//crear
            std::cout << "create order" << std::endl;
			int u_to_create = e.getX();
			//si el tech level no le da salgo
			if ((it->second)->getTechLvl() < getTechLvlFromUnit(u_to_create)) return;
			(it->second)->create(u_to_create, getFabTimeFromUnit(u_to_create)*10);
			}
			return;
			
		/*
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
	
	//bucle leo eventos, ejecuto y envio cambios a jugadores
	int s = 1;
	while(s > 0 && running){
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

            /*
			if (!event_list.empty()){
				Event e = event_list.front();
				event_list.pop();
				eventHandle(e, units);
			}
            */
			
			//actualizo las undiades (pendiente: crear una func aparte)
			
			for (auto it = units.begin(); it != units.end(); ++it){
				unit *u = it->second;
				actualizer(it->first, *u, units, mapa, 100, id_unit_counter, p_info);
			}
			
			usleep(100000);
			
			//envio los tech levels
			//p_info tiene la info de todos los players y un puntero a su protocolo para enviar
			p_info.sendUpdateTechLvl();
			//envio actualizacion de las unidades
            for (auto it = protocols.begin(); it != protocols.end(); ++it){
                 s = (*it)->sendActualization(units);
            }
			
			//limpio los fiambres
			unit_cleaner();
			
			//check si gano alguien, o si perdio
			/*
			if (NO_WINNER != checkVictory()){}
				running = false;
			}
			*/
	}
	
	//limpio unidades al final del juego
	std::cout << "delete units" << std::endl;
	for (auto it = units.begin(); it != units.end(); ++it){
		delete it->second;
	}
	
	for (auto it = protocols.begin(); it != protocols.end(); ++it){
		delete (*it);
	}
	
	std::cout << "juego out" << std::endl;	
	
	
	return;
}