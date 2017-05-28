#ifndef JUEGO_H
#define JUEGO_H

#include "../common/Thread.h"
#include "../common/Socket.h"
#include "../common/Lock.h"
#include "Event.h"
#include <mutex>
#include <vector>
#include <queue>
#include "gameMap.h"
#include "unit.h"

class juego: public tThread{
private:
		std::string creator;
		int max_players;
		gameMap mapa;
		std::queue<Event> event_list;
		std::vector<unit*> units;
		std::vector<tSocket*> cli_skts;
		std::mutex game_m; //juego esta protegido
		std::mutex &cli_m; //socket sincronizar con clientes
	public:
		juego(std::vector<tSocket*> &skts, std::mutex &cli_m);
		void run() override;
		void stop();
		void take_event(Event &e); //para apsarle los eventos desde los clientManager
		void sendInit();
};

#endif