#ifndef TCLIENTMANAGER_H
#define TCLIENTMANAGER_H

#include "Thread.h"
#include "Socket.h"
#include <mutex>

class tClientManager: public tThread{
	private:
		tSocket cli_skt;
		std::mutex &manager_m;
	public:
		tClientManager(tSocket cli_skt, std::mutex &manager_m);
		void run() override;
		void stop();
};

#endif
