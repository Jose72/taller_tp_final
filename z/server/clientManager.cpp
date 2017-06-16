#include "clientManager.h"
#include <string>
#include <iostream>
#include "unit.h"
#include "actualizeUnit.h"
#include <vector>
#include "string.h"
#include <mutex>
#include <unistd.h>
#include "../common/Lock.h"
#include "Protocol.h"
#include "infoPlayer.h"
#include "gameList.h"

#include "juego.h"

tClientManager::tClientManager(int id, tSocket cli_s, gameList &jgs, 
std::mutex &manager_m): id_client(id), cli_skt(std::move(cli_s)), 
manager_m(manager_m), juegos(jgs), end_game(false), j(nullptr) {}



//enviar y recibir (protocolo envia size primero, son del tp3) cambiarlos!!!

//tiene que haber dos protocolos:
//antes de empezar la partida y durante el juego

int receiveMessage(tSocket &skt_cli, std::string &msg){
	int s;
	int size_msg = 0;//aux para tamaño 
	s = skt_cli.receive((char *)&size_msg, sizeof(int)); //recivo tam msg
	//Reservo tamaño mensaje
	char* buff = new char [size_msg + 1];
	buff[size_msg]='\0';
	s = skt_cli.receive(buff, size_msg);
	//std::cout << "msg from client: " << buff << std::endl;
	msg = std::string(buff);
	delete [] buff;
	return s;
}	

int sendMessage(tSocket &skt_cli, std::string &msg_to_send){
	int s;
	int size_msg = msg_to_send.size(); //htonl
	//std::cout << "tam msg to send: " << size_msg << std::endl;
	s = skt_cli.send((char*)&size_msg, sizeof(size_msg));
	s = skt_cli.send(&msg_to_send[0u], size_msg);
	return s;
}

int tClientManager::gameSelection(){
	serverProtocol prot(cli_skt);

	int code = -1;
	cli_skt.receive((char*)&code, 4);
	code = ntohl(code);

	if (code == CREATE_GAME) {
		//envio confirmacion
		int confirm = htonl(0);
		cli_skt.send((char*)&confirm, 4);

		//recibo datos
		int cant_p = -1;
		cli_skt.receive((char*)&cant_p, 4);
		cant_p = ntohl(cant_p);

		int type_game = -1;
		cli_skt.receive((char*)&type_game, 4);
		type_game = ntohl(type_game);

		int teams = -1;
		cli_skt.receive((char*)&teams, 4);
		teams = ntohl(teams);

		//std::cout << "cant p: " << cant_p << std::endl;
		//std::cout << "gem: " << type_game << std::endl;
		//std::cout << "tcant eq: " << teams << std::endl;
		
		//creo el juego
		//harcodeo
		j = new juego(id_client, cant_p, DEATHMATCH, teams);
		j->clientJoin(id_client, &cli_skt);
		//pusheo en el vector
		juegos.push_back(j);

		//envio confirmacion
		cli_skt.send((char*)&confirm, 4);


		//espero hasta que esten todos listos
		while (!j->readyToStart() && !end_game){
			usleep(200000);
		}
		//si sali del loop porque se acaba el juego, salgo del manager
		if (end_game) return -1;


		//que el juego envie datos iniciales
		j->sendInit();

		//empiezo el juego
		j->start();
		return 0;

	}
	if (code == JOIN_GAME){ //si seleccione unirme

		//envio confirmacion
		int confirm = htonl(0);
		cli_skt.send((char*)&confirm, 4);


		
		int cant_games;
		std::vector<int> des;
		juegos.descriptionGames(des, cant_games);
		
		//envio cant juegos
		cant_games = htonl(juegos.size());
		cli_skt.send((char*)&cant_games, 4);
		
		//loop envio descripcion de juegos
		for (auto it = des.begin(); it != des.end(); ++it){
			int i = (*it);
			i = htonl(i);
			cli_skt.send((char*)&i, 4);
		}
		
		//recibir codigo
		int g_to_join;
		cli_skt.receive((char*)&g_to_join, 4);
		g_to_join = ntohl(g_to_join);
		std::cout << "g_to join: "  << g_to_join << std::endl;

		if (0 == juegos.joinGame(id_client, &cli_skt, &j, g_to_join)){ 
			
			//envio confirmacion de que me uni
			int confirm = htonl(0);
			cli_skt.send((char*)&confirm, 4);
			
			//espero a que todos esten listos
			while (!j->readyToStart() && !end_game){
				usleep(200000);
			}
			
			//si hubo error salgo
			if (end_game) return -1;
			return 0;
			
		} else {
			//envio que salio mal
			std::cout << "no joineo: " << std::endl;
			int confirm = htonl(1);
			cli_skt.send((char*)&confirm, 4);
			
			return 1; 
		}
		return 0;
	}
	
	int confirm = htonl(1);
	cli_skt.send((char*)&confirm, 4);
	return 1;
}


void tClientManager::stop(){
		std::cout << "manager stop" << std::endl;	
		end_game = true;
        cli_skt.shutdown(SHUT_RDWR);
		std::cout << "manager stop out" << std::endl;	
}

void tClientManager::run(){
	std::string player_name;
	std::mutex mmm;
	serverProtocol protocolo(cli_skt);

	//enviar id cliente;
	protocolo.send_id_client(id_client);
	
	///////////////////////////////////////////////////////////
	////PROTOCOLO NUEVO
	
	
	bool ok = false;
	while (!ok && !end_game){
		int i = this->gameSelection();
		if (i == 0) ok = true; //todo bien
		if (i == -1) return; //se rompio algo y hay que salir del manager
	}
	
	
	
	
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//HARDCODEO DE COMUNICACION APRA CREAR O UNISE (LO VIEJO)
	/*
	//si seleccione nuevo juego
	if (id_client == 1) {
		//creo el juego
		//hardcodeado cant jugadores
		j = new juego(id_client, 1, DEATHMATCH, 0);
		j->clientJoin(id_client, &cli_skt);
		//pusheo en el vector
		juegos.push_back(j);


		//espero hasta que esten todos listos
		while (!j->readyToStart() && !end_game){
			usleep(200000);
		}
		//si sali del loop porque se acaba el juego, salgo del manager
		if (end_game) return;


		//que el juego envie datos iniciales
		j->sendInit();

		//empiezo el juego
		j->start();

	} else { //si seleccione unirme
		//enviar lista de los juegos
		//busco en el vector de juegos

		//HARDOCDEADO
		if (0 == juegos.joinGame(id_client, &cli_skt, j, 1)){ //si hay juegos
			//espero a que todos esten listos
			while (!j->readyToStart() && !end_game){
				usleep(200000);
			}
			if (end_game) return;
		} else {
			return; //si no hay juegos salgo
		}

	}
	*/
	//////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	
	std::cout << "empezo client: " << id_client << std::endl;	
	
	int s = 1;
	while (s > 0) {
		/*
		std::cout << "start taking event: " << std::endl;
		*/
		
		Event e;
		s = protocolo.receive_event(e);
		
		if (s > 0) {
			//el juego tiene el mutex
			j->take_event(e);
		}
	}
	
	
	std::cout << "manager out" << std::endl;	

	return;
}
