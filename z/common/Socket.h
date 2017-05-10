#ifndef TSOCKET_H
#define TSOCKET_H

#include <netdb.h>

class tSocket {
	private:
		int skt;
		
	public:
		//aplicar asignacion por movimiento
		tSocket();
		~tSocket();
		void bindAndListen(int &port_number);
		void connect(char *ip_address, int &port_number);
		void accept(tSocket &accepted_socket);
		int send(const char* buffer, size_t length);
		int receive(char* buffer, size_t length);
		void shutdown(int how);
		tSocket(const tSocket&) = delete;
        tSocket& operator=(const tSocket&) = delete;
		tSocket(tSocket&& other);
        tSocket& operator=(tSocket&& other);
};

#endif
