#ifndef TCLIENTMANAGER_H
#define TCLIENTMANAGER_H


#include "../common/Thread.h"
#include "../common/Socket.h"
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
