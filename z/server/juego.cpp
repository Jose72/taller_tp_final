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
	for (auto it = cli_skts.begin(); it != cli_skts.end(); ++it){
		(*it)->shutdown(SHUT_RDWR);
	}
}

void juego::take_event(Event &e){
	tLock l(game_m);//lockeo
	event_list.push(e);
	return;
}

void juego::run(){
	
	
	//mapa codes de las casillas
	int map_codes[100] = {0};
	map_codes[15] = 1;
	map_codes[16] = 1;
	map_codes[17] = 1;
	map_codes[18] = 1;
	map_codes[31] = 1;
	map_codes[32] = 1;
	map_codes[33] = 1;
	map_codes[34] = 1;
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
	
	//genero unidad 
	unit u1(ROBOT, GRUNT, 35, 18, 300, ROBOT_SPEED);
	int unit_code = GRUNT;
	int xx = u1.getX();
	int yy = u1.getY();
	int unit_cant = 1;
	
	std::cout << "map size: " << sss << std::endl;
	
	//cargo mi mapa
	gameMap mapa(map_codes, sss);
	
	//paso el mapa y unidades a todos
	for (auto it = cli_skts.begin(); it != cli_skts.end(); ++it){
		(*it)->send((char*) &sss, sizeof(int));
		(*it)->send((char*) &map_codes, sizeof(int) * sss);
		(*it)->send((char*) &unit_cant, sizeof(int));
		(*it)->send((char*) &unit_code, sizeof(int));
		(*it)->send((char*) &xx, sizeof(int));
		(*it)->send((char*) &yy, sizeof(int));
	}
	
	actualizeUnit actualizer;
	
	//bucle leo eventos, ejecuto y envio cambios a jugadores
	int s = 1;
	while(s > 0){
			
			//lockeo cola de evntos
			game_m.lock();
			if (!event_list.empty()){
				Event e = event_list.front();
				event_list.pop();
				//esto esta harcodeado, tendria que llamar a una funcion
				//que identifique la op y ejecute (handler)
				u1.move(e.takeX(), e.takeY());
			}
			game_m.unlock();
			//deslockeo
			
			//actualizo
			actualizer(u1, mapa, 1);
			sleep(1);
			//envio 
			int xx = u1.getX();
			int yy = u1.getY();
			for (auto it = cli_skts.begin(); it != cli_skts.end(); ++it){
				s = (*it)->send((char*) &xx, sizeof(int));
				s = (*it)->send((char*) &yy, sizeof(int));
			}
			
			//si termine de mover salgo de loop
			//solo para cortar el ejemplo
			if (!u1.isMoving()) break;
	}
	
	//señal de que termino, mando a todos
	int b = -1;
	for (auto it = cli_skts.begin(); it != cli_skts.end(); ++it){
		(*it)->send((char*) &b, sizeof(int));
	}
	
	return;
}