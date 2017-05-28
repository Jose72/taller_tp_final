
#include "server.h"

#include "string.h"
#include <iostream>
#include <vector>



tServer::tServer(int port) : serv_skt(tSocket()) {
	port_number = port;
	acepter_open = true;
}


void tServer::stop(){
		std::cout << "server stop" << std::endl;	
		acepter_open = false;
		serv_skt.shutdown(SHUT_RDWR);
		
		for (unsigned int j = 0; j < client_mngrs.size(); j++){
			//paro y joineo los managers
			client_mngrs[j]->stop();
			client_mngrs[j]->join();
			delete client_mngrs[j];
		}
		
		for (unsigned int j = 0; j < juegos.size(); j++){
			//paro y joineo los juegos
			juegos[j]->stop();
			juegos[j]->join();
			delete juegos[j];
		}
		
		std::cout << "server stop out" << std::endl;	
}


//este es el while aceptador
int tServer::processClient(){
	int client_id_count = 0;
	
	while (acepter_open){ //mientras aceptador abierto
		try {
		serv_skt.bindAndListen(port_number);
			try {
				//creo socket para cliente
				tSocket new_skt = serv_skt.accept();
				//std::cout << "new client" << std::endl;
				
				tClientManager *cli_man = new tClientManager(client_id_count+1, std::move(new_skt),
				juegos, m); //paso al manager
				client_mngrs.push_back(cli_man);
				cli_man->start();
				
				
			} catch(...) {} //catch del aceptar
		} catch(...) {//catch del bind and listen
			acepter_open = false;
		}
	}	
	
	std::cout << "server out" << std::endl;	
	return 0;
}

void tServer::run(){;
	processClient();
}
