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
manager_m(manager_m), juegos(jgs), end_game(false), j(nullptr), ended(false) {}


bool tClientManager::readyToClean(){
	return ended;
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
		
		//si la cant de jugadores es menor o igual a 1 da error
		if (cant_p <= 1 ){
			return 1;
		}
		
		//creo el juego
		//harcodeo
		
		//si es deathmantc equipos = juagdores
		int teams2 = teams;
		if (type_game == DEATHMATCH) {
			teams2 = cant_p;
		} else {
			//sino tienen que ser equipos parejos
			if ((cant_p % teams) != 0 || teams <= 1) return 1;
		}
		
		//hardocdeado DEATHMATCH
		j = new juego(id_client, cant_p, type_game, teams2);
		j->clientJoin(id_client, &cli_skt, 1);
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

		//RECIBIR EL TEAM!!!!!!!!!!
		if (0 == juegos.joinGame(id_client, &cli_skt, &j, g_to_join, 2)){ 
			
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
		if (i == -1) {
			ended = true;
			return; //se rompio algo y hay que salir del manager
		}
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	std::cout << "empezo client: " << id_client << std::endl;	
	
	int s = 1;
	while (s > 0 && !end_game) {
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
	ended = true;
	return;
}
