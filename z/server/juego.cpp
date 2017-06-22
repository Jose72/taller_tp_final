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

//cant jugadores
//tipo de juego(deathmatch o equipos)
//cant equipos
juego::juego(int creator, int cant_players, int game_t, int cant_teams): 
id_creator(creator), max_players(cant_players), teams(cant_teams), 
game_type(game_t), builder(u_info), g_info(infoGame(cant_players, 
game_t, cant_teams)), running(false), started(false), ended(false) {
	id_unit_counter = 1; //se empieza contando desde 1
}

bool juego::gameStarted(){
	return started;
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
	for (int i = 1; i <= teams; ++i){
		if (DEFEAT == g_info.updateVictoryCond(i)){
			//defeatHandler df;
			//si fue derrotado, hay que ver que hacer con las unidades
			//df.defeatPlayer(i, units);
		}
	}
	//me fijo si hay ganador
	int winner = g_info.checkForWinner();
	if (winner != NO_WINNER){
		std::cout << "WINNER: " << winner << std::endl;
		for (auto it = protocols.begin(); it != protocols.end(); ++it){
			//hay que enviarles a todos que termino la partida
			(*it)->sendVictory(winner);
		}
		
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
				delete it->second;
				it = units.erase(it);
				break;
			}
			default:{
				++it;
				break;
			}
			
		}
		/*
		//si la unidad esta muerta o fue borrada
		if (u->isDead() || u.getState() == ERASED) {
			death_h.death(*u, units, id_unit_counter, mapa, g_info);//handler por si tiene q hacer algo
			//si no es un edificio lo elimino
			if (not_edificio){
				delete it->second;
				it = units.erase(it); // borro de la lista
				
			}
		} else {
			
		}
		*/ 
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
		cli_skts.push_back(cli_s);
		
		// protocolos
		serverProtocol *p = new serverProtocol(*cli_s);
		protocols.push_back(p);
		
		cli_ids.push_back(cli_id);
		g_info.addNewPlayer(cli_id, p, team_n);
		return 0;
	}
	return 1;
}

void juego::sendInit(){
	JsonHandler jsonHandler;
	std::vector<int> mapDes = jsonHandler.jsonToMap();
	mapa = gameMap(mapDes);
    jsonHandler.jsonToUnits(id_unit_counter,builder,units);

    /*
	//unit* u1 = new unit(1, GRUNT, 60, 15);
	unit *u1 = builder.build(GRUNT, 1, 300, 400);
	units.insert(std::pair<int,unit*>(id_unit_counter,u1));
	id_unit_counter++;

	unit *u2 = builder.build(FLAG, 270, 15);
	units.insert(std::pair<int,unit*>(id_unit_counter,u2));
	id_unit_counter++;

	unit *u3 = builder.build(FORT, 1, 32, 32);
	units.insert(std::pair<int,unit*>(id_unit_counter,u3));
	id_unit_counter++;

	unit *u4 = builder.build(FORT ,2 ,640, 640);
	units.insert(std::pair<int,unit*>(id_unit_counter,u4));
	id_unit_counter++;
	
	unit *u5 = builder.build(PYRO, 1, 300, 200);
	units.insert(std::pair<int,unit*>(id_unit_counter,u5));
	id_unit_counter++;
	
	unit *u6 = builder.build(PYRO, 1, 300, 180);
	units.insert(std::pair<int,unit*>(id_unit_counter,u6));
	id_unit_counter++;
	
	unit *u7 = builder.build(PYRO, 1, 300, 220);
	units.insert(std::pair<int,unit*>(id_unit_counter,u7));
	id_unit_counter++;
	
	unit *u8 = builder.build(GRUNT, 2, 10, 230);
	units.insert(std::pair<int,unit*>(id_unit_counter,u8));
	id_unit_counter++;

	unit *u9 = builder.build(GRUNT, 2, 20, 230);
	units.insert(std::pair<int,unit*>(id_unit_counter,u9));
	id_unit_counter++;
     */
	
	unit *u1 = builder.build(PYRO, 1, 150, 400);
	units.insert(std::pair<int,unit*>(id_unit_counter,u1));
	id_unit_counter++;
	
	unit *u8 = builder.build(GRUNT, 2, 10, 230);
	units.insert(std::pair<int,unit*>(id_unit_counter,u8));
	id_unit_counter++;
	
	u8->move(287,431);
	
	///////////////77
	//TERRITORIOS HARDCODEADO
	unit *u2 = builder.build(FLAG, 50, 500);
	units.insert(std::pair<int,unit*>(id_unit_counter,u2));
	id_unit_counter++;
	
	unit *u3 = builder.build(VEHICLE_FACTORY, 0, 104, 520);
	units.insert(std::pair<int,unit*>(id_unit_counter,u3));
	id_unit_counter++;
	
	unit *u4 = builder.build(ROBOT_FACTORY, 0, 104, 680);
	units.insert(std::pair<int,unit*>(id_unit_counter,u4));
	id_unit_counter++;

	unit *u5 = builder.build(BRIDGE_H, 320, 680);
	units.insert(std::pair<int,unit*>(id_unit_counter,u5));
	id_unit_counter++;
	u5 = builder.build(BRIDGE_H, 384, 680);
	units.insert(std::pair<int,unit*>(id_unit_counter,u5));
	id_unit_counter++;
	u5 = builder.build(BRIDGE_H, 448, 680);
	units.insert(std::pair<int,unit*>(id_unit_counter,u5));
	id_unit_counter++;
	u5 = builder.build(BRIDGE_H, 512, 680);
	units.insert(std::pair<int,unit*>(id_unit_counter,u5));
	id_unit_counter++;
	u5 = builder.build(BRIDGE_H, 576, 680);
	units.insert(std::pair<int,unit*>(id_unit_counter,u5));
	id_unit_counter++;
	
	u5 = builder.build(JEEP, 0, 104, 800);
	units.insert(std::pair<int,unit*>(id_unit_counter,u5));
	id_unit_counter++;
	
	std::vector<unit*> fac;
	fac.push_back(u3);
	fac.push_back(u4);
	territory t(u2, fac);
	territorios.push_back(t);
	///////////////////////////////////
	
	
	
	//hay que inicilizar la info de cada equipo
	//codigo de equipo (owner), puntero a fuerte, cant incial de unidades
	//cant de unidades es solo robots y vehiculos, edificios no cuentan
	
	//mandar vector de fuertes por equipo (o un solo fuerte por equipo???)
    std::vector<unit*> forts_1;
    forts_1.push_back(units[1]);
    std::vector<unit*> forts_2;
    forts_2.push_back(units[2]);
    g_info.initializeTeam(1,forts_1, 1);
    g_info.initializeTeam(2,forts_2, 1);
    //g_info.initializePlayer(1, u3, 4);
	//g_info.initializePlayer(2, u4, 2);
	
	

	
	/*
	//probar con 3 juagdores
	unit *u10 = builder.build(FORT ,3 ,128, 640);
	units.insert(std::pair<int,unit*>(id_unit_counter,u10));
	id_unit_counter++;
	unit *u11 = builder.build(GRUNT ,3 ,200, 640);
	units.insert(std::pair<int,unit*>(id_unit_counter,u11));
	id_unit_counter++;
	std::vector<unit*> forts_3;
	forts_3.push_back(u10);
	g_info.initializeTeam(3,forts_3, 1);
	*/

		
	mapa.setBlocking(units);
	
	
	////////////////////////////////
	//ENVIAR NUMERO DE EQUIPO ANTES QUE TODO
	g_info.sendTeamNumbers();
	///////////////////////////////
	
	
	//protocol
	for (auto it = protocols.begin(); it != protocols.end(); ++it){
		(*it)->send_map(mapDes);
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
			int unit_uniq_code = it2->first;
			if (unit_uniq_code != e.getX()) return; //no encontro a la unidad
			
			//solo robots o vehiculos
			if (((it->second)->getClassId() == ROBOT || (it->second)->getClassId() == VEHICLE) && 
			(it2->second)->getUnitId() != FLAG) {
				(it->second)->attack(it2->second);
				}
			}
			return;
		
		case 2: 
			{
			//crear
            std::cout << "create order: " << e.getX() << std::endl;
			int u_to_create = e.getX();
			//si el tech level no le da salgo
			//if ((it->second)->getTechLvl() < getTechLvlFromUnit(u_to_create)) return;
			(it->second)->create(u_to_create, getFabTimeFromUnit(u_to_create)*10);
			
			return;
			}
		case 3: //conducir
			{
			//busco la unidad destino
			//si no es robot salgo
			std::cout << "drive order: " << e.getX() << std::endl;
			if (it->second->getClassId() != ROBOT) return;
			std::map<int,unit*>::iterator it2;
			it2 = units.find(e.getX());
			if (it2->first != e.getX()) return; //no encontro a la unidad
			std::cout << "drive ok: " << e.getX() << std::endl;
			(it->second)->drive(it2->second);
			return;
			}
	}
}

void juego::run(){
	started = true;
	running = true;
	//mapa codes de las casillas
	
	actualizeUnit actualizer(builder, u_info);
	
	//bucle leo eventos, ejecuto y envio cambios a jugadores
	int s = 1;
	while(s > 0 && running){
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

			//actualizo las undiades (pendiente: crear una func aparte)
			for (auto it = units.begin(); it != units.end(); ++it){
				unit *u = it->second;
				actualizer(it->first, *u, units, mapa, 100, id_unit_counter, g_info);
			}
			
			//actualzicion de territorios
			for (auto it = territorios.begin(); it != territorios.end(); ++it){
				it->changeOwnership();
			}
			
			//HARCIDEO - CAMBIAR
			//envio los tech levels -----  NO NECESARIO - ARREGLAR
			for (auto it = protocols.begin(); it != protocols.end(); ++it){
                 s = (*it)->sendUpdateTechLvl(5);
            }
			
			
			
			//envio actualizacion de las unidades
            for (auto it = protocols.begin(); it != protocols.end(); ++it){
                 s = (*it)->sendActualization(units);
            }
			
			//limpio los fiambres
			unit_cleaner();
			
			//check si gano alguien, o si perdio
			if (NO_WINNER != checkVictory()){
				running = false;
			}
			
			
		int elapsed_time = (clock() - Start) * 1000000 / CLOCKS_PER_SEC;
		int sleep_time = 100000 - elapsed_time;
		if (sleep_time < 0) sleep_time = 0;
		//std::cout << "Time Difference: " << sleep_time << std::endl;
		usleep(sleep_time);
			
	}
	
	//limpio unidades al final del juego
	std::cout << "delete units" << std::endl;
	for (auto it = units.begin(); it != units.end(); ++it){
		delete it->second;
	}
	//y los protocolos
	for (auto it = protocols.begin(); it != protocols.end(); ++it){
		delete (*it);
	}
	
	std::cout << "juego out" << std::endl;	
	
	ended = true;
	return;
}
