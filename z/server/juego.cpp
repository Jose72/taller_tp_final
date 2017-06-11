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
juego::juego(int cant_players, int game_t, int cant_teams): 
max_players(cant_players), p_info(infoPlayers(cant_players, 
game_t, cant_teams)), running(false) {
	id_unit_counter = 1; //se empieza contando desde 1
}

bool juego::isRunning(){
	return running;
}

void juego::checkVictory(){
	//para cada cliente chequeo condiciones de vict
	for (auto it = cli_ids.begin(); it != cli_ids.end(); ++it){
		if (DEFEAT == p_info.checkVictoryConditions(*it)){
			//si fue derrotado, busco sus unidades y las seteo en DEFEATED
			for (auto it2 = units.begin(); it2 != units.end(); ++it2){
				unit *u = (it2->second);
				if (u->getOwner() == (*it)){
					u->changeState(DEFEATED);
				}
			}
		}
	}
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
		if (u->isDead()) {
			death_h.death(*u, units);//handler por si tiene q hacer algo
			//std::cout << "unit " << it->first << " dead" << std::endl;
			delete it->second; // libero mem
			it = units.erase(it); // borro de la lista
		} else {
			++it;
		}
	}
}

void juego::take_event(Event &e){
	tLock l(game_m);//lockeo
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
	if (cli_skts.size() < (unsigned int) max_players){
		cli_skts.push_back(cli_s);
		
		// protocolos
		protocols.push_back(serverProtocol(*cli_s));
		
		//players_info.push_back(infoPlayer(cli_id));
		
		cli_ids.push_back(cli_id);
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
	unit *u1 = builder.build(GRUNT, 1, 70, 15);
	units.insert(std::pair<int,unit*>((units.size()+1),u1));
	id_unit_counter++;



	unit *u2 = builder.build(GRUNT, 2, 160, 15);
	units.insert(std::pair<int,unit*>((units.size()+1),u2));
	id_unit_counter++;

	unit *u3 = builder.build(GRUNT, 1,40, 40);
	units.insert(std::pair<int,unit*>((units.size()+1),u3));
	id_unit_counter++;

	/**unit *u4 = builder.build(GRUNT, 2,280, 280);
	units.insert(std::pair<int,unit*>((units.size()+1),u4));
	id_unit_counter++;*/

	unit *u5 = builder.build(ROBOT_FACTORY, 1,0, 200);
	units.insert(std::pair<int,unit*>((units.size()+1),u5));
	id_unit_counter++;

	unit *u6 = builder.build(VEHICLE_FACTORY, 1,100, 200);
	units.insert(std::pair<int,unit*>((units.size()+1),u6));
	id_unit_counter++;

	unit *u7 = builder.build(FORT, 1,200, 200);
	units.insert(std::pair<int,unit*>((units.size()+1),u7));
	id_unit_counter++;

	//protocol
	for (auto it = protocols.begin(); it != protocols.end(); ++it){
		it->send_map((int*)&map_codes,sss);
		it->send_units_game(units);
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
			//if ((it->second)->getClassId() == ROBOT || (it->second)->getClassId() == VEHICLE) {
			(it->second)->move(e.getX(),e.getY());
			//}
			
			}
			return;
			
		case 1:
			{
			//ataque
            std::cout << "ataq order" << std::endl;
			//moverse
			std::map<int,unit*>::iterator it2;
			it2 = units.find(e.getX());
			
			if (it2->first != e.getX()) return; //no encontro a la unidad
			
			//solo robots o vehiculos
			//if ((it->second)->getClassId() == ROBOT || (it->second)->getClassId() == VEHICLE) {
			(it->second)->attack(it2->second);
			//}
			}
			return;
		
		case 2: 
			{
			//crear
            std::cout << "create order" << std::endl;
			int u_to_create = e.getX();
			//si el tech level no le da salgo
			if ((it->second)->getTechLvl() < getTechLvlFromUnit(u_to_create)) return;
			(it->second)->create(u_to_create, getFabTimeFromUnit(u_to_create)*1000);
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
	infoPlayers p_info(4, DEATHMATCH, 0);
	
	//bucle leo eventos, ejecuto y envio cambios a jugadores
	int s = 1;
	while(s > 0){
			//std::cout << "loop juego" << std::endl;
			//lockeo cola de evntos


            int c = event_list.size();
			int i = 0;
            while (!event_list.empty() && i < c) {
                game_m.lock();
                Event e = event_list.front();
                event_list.pop();
                game_m.unlock();
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
			//deslockeo

			
			
			//actualizo las undiades (pendiente: crear una func aparte)
			std::set<int> dead_units;
			std::set<int> actualized_units;
			for (auto it = units.begin(); it != units.end(); ++it){
				unit *u = it->second;
				actualizer(it->first, *u, units, mapa, 100, id_unit_counter, p_info);
			}
			
			usleep(100000);
			
            for (auto it = protocols.begin(); it != protocols.end(); ++it){
                 s = it->sendActualization(units);
            }
			
			//limpio los fiambres
            //std::cout << "units clean" << std::endl;
			unit_cleaner();
	}
	
	
	std::cout << "delete units" << std::endl;
	for (auto it = units.begin(); it != units.end(); ++it){
		delete it->second;
	}
	

	std::cout << "juego out" << std::endl;	
	
	
	return;
}