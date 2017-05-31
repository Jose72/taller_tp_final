#ifndef JUEGO_H
#define JUEGO_H

#include "../common/Thread.h"
#include "../common/Socket.h"
#include "../common/Lock.h"
#include "Event.h"
#include <map>
#include <mutex>
#include <vector>
#include <queue>
#include "gameMap.h"
#include "unit.h"
#include "unitBuilder.h"

class juego: public tThread{
	private:
		int id_creator;
		std::string creator; //creador del mapa
		int max_players;  //cant de jugadores
		gameMap mapa; //mapa
		unitBuilder builder;
		int id_unit_counter;
		std::queue<Event> event_list; //cola de eventos
		std::map<int, unit*> units; //mapa para unidades con id unica cada una
		std::vector<tSocket*> cli_skts; //vector de sockets de clientes
		std::vector<int> cli_ids; //vector id de clietnes, necesario??????
		std::mutex game_m; 
		std::mutex &cli_m; //proteger eventos
		bool running;
	
	public:
		juego(int cant_players, tSocket* creator_skt, std::mutex &cli_m);
		void run() override;
		void stop();
		void take_event(Event &e); //para apsarle los eventos desde los clientManager
		void sendInit();
		bool readyToStart();
		int clientJoin(tSocket *cli_s);
		bool isRunning();
};

#endif