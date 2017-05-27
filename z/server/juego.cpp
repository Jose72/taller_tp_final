#include "juego.h"
#include <vector>
#include "gameMap.h"
#include <iostream>
#include "actualizeUnit.h"
#include <unistd.h>


juego::juego(std::vector<tSocket*> &skts, std::mutex &cli_m): cli_m(cli_m){
	cli_skts = skts;
}

void juego::stop(){
	
	/*
	for (auto it = cli_skts.begin(); it != cli_skts.end(); ++it){
		(*it)->shutdown(SHUT_RDWR);
	}
	*/
}

void juego::take_event(Event &e){
	tLock l(game_m);//lockeo
	event_list.push(e);
	return;
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
	
	/*
	std::vector<int> tile_codes;
	for (int i = 0; i < 100; i++){
		tile_codes.push_back(map_codes[i]);
	}
	*/
	
	std::cout << "map size: " << sss << std::endl;
	
	//cargo mi mapa
	mapa = gameMap(map_codes, sss);
	
	cli_skts[0]->send((char*) &sss, sizeof(int));
	cli_skts[0]->send((char*) &map_codes, sizeof(int) * sss);
	
	/*
	//paso el mapa y unidades a todos
	for (auto it = cli_skts.begin(); it != cli_skts.end(); ++it){
		(*it)->send((char*) &sss, sizeof(int));
		(*it)->send((char*) &map_codes, sizeof(int) * sss);
		(*it)->send((char*) &unit_cant, sizeof(int));
		(*it)->send((char*) &unit_code, sizeof(int));
		(*it)->send((char*) &xx, sizeof(int));
		(*it)->send((char*) &yy, sizeof(int));
	}
	*/
	
	unit* u1 = new unit(ROBOT, GRUNT, 60, 15, 300, ROBOT_SPEED);
	units.push_back(u1);
	int unit_code = GRUNT;
	int xx = u1->getX();
	int yy = u1->getY();
	int unit_cant = 1;
	cli_skts[0]->send((char*) &unit_cant, sizeof(int));
	cli_skts[0]->send((char*) &unit_code, sizeof(int));
	cli_skts[0]->send((char*) &xx, sizeof(int));
	cli_skts[0]->send((char*) &yy, sizeof(int));
}

void juego::run(){
	
	
	//mapa codes de las casillas
	
	
	
	
	actualizeUnit actualizer;
	unit* u1 = units[0];
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
				u1->move(e.takeX(), e.takeY());
			}
			//deslockeo
			cli_m.unlock();
			
			
			//actualizo
			actualizer(*u1, mapa, 1);
			sleep(1);
			int xx = u1->getX();
			int yy = u1->getY();
			s = cli_skts[0]->send((char*) &xx, sizeof(int));
			s = cli_skts[0]->send((char*) &yy, sizeof(int));
			
			//si termine de mover salgo de loop
			//solo para cortar el ejemplo
			if (!u1->isMoving()) {
				std::cout << "termino mov" << std::endl;
				break;
			}
				
	}
	
	
	std::cout << "delete units" << std::endl;
	for (unsigned int i = 0; i < units.size(); i++){
		delete units[i];
	}
	
	int b = -1;
	for (auto it = cli_skts.begin(); it != cli_skts.end(); ++it){
		(*it)->send((char*) &b, sizeof(int));
	}
	
	
	
	return;
}