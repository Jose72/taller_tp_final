#ifndef TCLIENTMANAGER_H
#define TCLIENTMANAGER_H


#include "../common/Thread.h"
#include "../common/Socket.h"
#include <mutex>
#include "juego.h"

class tClientManager: public tThread{
	private:
		int id_client;
		tSocket cli_skt;
		std::mutex &manager_m;
		juego *j;
	public:
		tClientManager(int id, tSocket cli_skt, std::mutex &manager_m);
		~tClientManager();
		void run() override;
		void stop();
};

#endif
