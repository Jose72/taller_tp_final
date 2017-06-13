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
#include "infoPlayer.h"
#include "Protocol.h"
#include <string>

class juego: public tThread{
	private:
		int id_creator;
		std::string creator; //creador del mapa
		int max_players;  //cant de jugadores
		int teams;
		int game_type;
		gameMap mapa; //mapa
		unitBuilder builder;
		int team_count;
		int id_unit_counter;
		std::queue<Event> event_list; //cola de eventos
		std::map<int, unit*> units; //mapa para unidades con id unica cada una
		std::vector<tSocket*> cli_skts; //vector de sockets de clientes
		std::vector<serverProtocol*> protocols;//vector de protocolos de clientes
		infoPlayers p_info; //info global de jugadores/equipos
		std::vector<int> cli_ids; //vector id de clietnes, necesario??????
		std::mutex event_m; //proteger eventos
		std::mutex game_m;
		bool running;
		bool started;
		
		void eventHandle(Event &e, std::map<int, unit*> &units);
		int checkVictory();
		void unit_cleaner();
		void unitGameCreate();
	
	public:
		juego(int creator, int cant_players, int game_type, int cant_teams);
		void run() override;
		void stop();
		void take_event(Event &e); //para pasarle los eventos desde los clientManager
		void sendInit();
		bool readyToStart();
		int clientJoin(int cli_id, tSocket *cli_s);
		bool gameStarted();
		void getDescription(int &creat, int &max_p, int &cant_p, int &game_t, int &cant_t);
		bool isCreator(int c);
};

#endif