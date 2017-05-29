#include "juego.h"
#include <vector>
#include "gameMap.h"
#include <map>
#include <iostream>
#include "actualizeUnit.h"
#include <unistd.h>


juego::juego(tSocket* creator_skt, std::mutex &cli_m): cli_m(cli_m){
	cli_skts.push_back(creator_skt);
	id_unit_counter = 1; //se empieza contando desde 1
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
	//tLock l(game_m);//lockeo
	std::cout << "event push" << std::endl;
	event_list.push(e);
	return;
}

bool juego::readyToStart(){
	//si tengo tantos clientes como jugadores espero
	if (cli_skts.size() == (unsigned int) max_players) return true;
	return false;
}

int juego::clientJoin(tSocket *cli_s){
	if (cli_skts.size() < (unsigned int) max_players){
		cli_skts.push_back(cli_s);
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
	
	
	unit* u1 = new unit(ROBOT, GRUNT, 60, 15, 300, ROBOT_SPEED);
	//units.push_back(u1);
	
	units.insert(std::pair<int,unit*>(id_unit_counter,u1));
	id_unit_counter++;
	
	int unit_code = GRUNT;
	int xx = u1->getX();
	int yy = u1->getY();
	int unit_cant = 1;
	
	/*
	cli_skts[0]->send((char*) &sss, sizeof(int));
	cli_skts[0]->send((char*) &map_codes, sizeof(int) * sss);
	cli_skts[0]->send((char*) &unit_cant, sizeof(int));
	cli_skts[0]->send((char*) &unit_code, sizeof(int));
	cli_skts[0]->send((char*) &xx, sizeof(int));
	cli_skts[0]->send((char*) &yy, sizeof(int));
	*/
	
	//paso el mapa y unidades a todos
	for (auto it = cli_skts.begin(); it != cli_skts.end(); ++it){
		(*it)->send((char*) &sss, sizeof(int));
		(*it)->send((char*) &map_codes, sizeof(int) * sss);
		(*it)->send((char*) &unit_cant, sizeof(int));
		(*it)->send((char*) &unit_code, sizeof(int));
		(*it)->send((char*) &xx, sizeof(int));
		(*it)->send((char*) &yy, sizeof(int));
	}
	
	
	
	
}

void juego::run(){
	
	
	//mapa codes de las casillas
	
	actualizeUnit actualizer;
	
	//bucle leo eventos, ejecuto y envio cambios a jugadores
	int s = 1;
	while(s > 0){
			
			//lockeo cola de evntos
			cli_m.lock();
			if (!event_list.empty()){
				Event e = event_list.front();
				event_list.pop();
				//esto esta harcodeado, tendria que llamar a una funcion
				//que identifique la op y ejecute (handler)
				std::map<int,unit*>::iterator it;
				it = units.find(e.getId());
				//find devuelte el iterador del elemento o el ultimo si no existe la key
				//hay que chequear que devolvio correctamente
				if (it->first == e.getId()){
					unit *u1 = it->second;
					u1->move(e.getX(), e.getY()); //hay que hacer un handler
				}
			}
			//deslockeo
			cli_m.unlock();
			
			
			//actualizo las undiades --- crear una func aparte!!!!!!
			for (auto it = units.begin(); it != units.end(); ++it){
				unit *u1 = it->second;
				actualizer(*u1, units, mapa, 1);
				sleep(1);
				int xx = u1->getX();
				int yy = u1->getY();
				for (auto it = cli_skts.begin(); it != cli_skts.end(); ++it){
					s = cli_skts[0]->send((char*) &xx, sizeof(int));
					s = cli_skts[0]->send((char*) &yy, sizeof(int));
				}
			}
			
	}
	
	
	std::cout << "delete units" << std::endl;
	for (auto it = units.begin(); it != units.end(); ++it){
		delete it->second;
	}
	
	/*
	
	for (unsigned int i = 0; i < units.size(); i++){
		if (units[i]) {
			delete units[i];
			units[i] = nullptr;
		}
	}
	*/
	std::cout << "juego out" << std::endl;	
	
	
	return;
}