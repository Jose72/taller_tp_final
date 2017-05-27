
#include "server.h"

#include "string.h"
#include <iostream>
#include <vector>



tServer::tServer(int port) : serv_skt(tSocket()) {
	port_number = port;
	acepter_open = true;
}


void tServer::stop(){
		acepter_open = false;
		serv_skt.shutdown(SHUT_RDWR);
		for (unsigned int j = 0; j < client_mngrs.size(); j++){
			//paro y joineo los managers
			client_mngrs[j]->stop();
			client_mngrs[j]->join();
			delete client_mngrs[j];
		}
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
				m); //paso al manager
				client_mngrs.push_back(cli_man);
				cli_man->start();
				
				//recibir numero, nuevo cliente (0) u segundo socket (id_cliente)
				/*
				int ident;
				new_skt.receive((char*) &ident, sizeof(int));
				
				if (ident == 0){ //si es un nuevo cliente
					tClientManager *cli_man = new tClientManager(client_id_count+1, std::move(new_skt),
					m); //paso al manager
					client_mngrs.push_back(cli_man);
					cli_man->start();
				} 
				
				//si el id esta dentro de los cli managares
				if ((int)client_mngrs.size() >= ident){
						client_mngrs[ident-1]->passSecondConnection(std::move(new_skt));
				}
				*/
				
			} catch(...) {} //catch del aceptar
		} catch(...) {//catch del bind and listen
			acepter_open = false;
		}
	}	
	return 0;
}

void tServer::run(){;
	processClient();
}
