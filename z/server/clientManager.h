#ifndef TCLIENTMANAGER_H
#define TCLIENTMANAGER_H


#include "../common/Thread.h"
#include "../common/Socket.h"
#include <mutex>
#include "juego.h"
#include "gameList.h"

#define CREATE_GAME 0
#define JOIN_GAME 1

class tClientManager: public tThread{
	private:
		int id_client;
		tSocket cli_skt;
		std::mutex &manager_m;
		gameList &juegos;
		std::string map_folder;
		std::string unit_info_path;
		bool end_game;
		juego *j;
		bool ended;

		int gameSelection();
	public:
		tClientManager(int id, tSocket cli_skt, gameList &jgs, 
		std::mutex &manager_m, std::string &map_folder, std::string &unit_info_path);
		void run() override;
		void stop();
		bool readyToClean();
};

#endif
