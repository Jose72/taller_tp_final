#ifndef TSERVER_H
#define TSERVER_H

#include <fstream>
#include <vector>
#include <string>
#include <mutex>

#include "../common/Socket.h"
#include "../common/Thread.h"
#include "clientManager.h"

class tServer: public tThread{
	private:
		int port_number;
		tSocket serv_skt;
		bool acepter_open;
		std::vector<tThread*> client_mngrs;
		std::mutex m;
	public:
		tServer(int port);
		void run() override;
		void stop() override;
		int processClient();
		bool accept(tSocket &skt);
};

#endif
