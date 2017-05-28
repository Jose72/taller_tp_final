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
		std::vector<int> cli_ids;
		std::mutex game_m;
		std::mutex &cli_m; //proteger eventos
	public:
		juego(tSocket* creator_skt, std::mutex &cli_m);
		void run() override;
		void stop();
		void take_event(Event &e); //para apsarle los eventos desde los clientManager
		void sendInit();
		bool readyToStart();
		int clientJoin(tSocket *cli_s);
};

#endif