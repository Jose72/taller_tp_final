
#include "server.h"

#include "string.h"
#include <iostream>
#include <vector>



tServer::tServer(int port, std::string &map_folder, std::string &unit_info_path): 
port_number(port), map_folder(map_folder), unit_info_path(unit_info_path), 
serv_skt(tSocket()), acepter_open(true) {}


void tServer::stop(){
		acepter_open = false;
		serv_skt.shutdown(SHUT_RDWR);
		
		for (unsigned int j = 0; j < client_mngrs.size(); j++){
			//paro y joineo los managers
			client_mngrs[j]->stop();
			client_mngrs[j]->join();
		}

		g_list.stopGames();
		g_list.cleanGames();
		
		for (unsigned int j = 0; j < client_mngrs.size(); j++){
			//limpio
			delete client_mngrs[j];
		}
}


//este es el while aceptador
int tServer::processClient(){
	int client_id_count = 1;
	while (acepter_open){ //mientras aceptador abierto
		try {
		serv_skt.bindAndListen(port_number);
			try {
				//creo socket para cliente
				tSocket new_skt = serv_skt.accept();
				
				tClientManager *cli_man = new tClientManager(client_id_count, std::move(new_skt),
				g_list, map_folder, unit_info_path); //paso al manager
				client_id_count++;
				client_mngrs.push_back(cli_man);
				cli_man->start();
				
				
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
