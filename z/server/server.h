#ifndef TSERVER_H
#define TSERVER_H

#include <fstream>
#include <vector>
#include <string>
#include <mutex>

#include "../common/Socket.h"
#include "../common/Thread.h"
#include "clientManager.h"
#include "juego.h"
#include "gameList.h"

class tServer: public tThread{
	private:
		int port_number;
		std::string map_folder;
		std::string unit_info_path;
		tSocket serv_skt;
		bool acepter_open;
		std::vector<tClientManager*> client_mngrs;
		gameList g_list;
		std::mutex m;
	public:
		tServer(int port, std::string &map_folder, std::string &unit_info_path);
		void run() override;
		void stop() override;
		int processClient();
		bool accept(tSocket &skt);
};

#endif
