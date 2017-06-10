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

#include "juego.h"

tClientManager::tClientManager(int id, tSocket cli_s, std::vector<juego*> & jgs, 
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
	//cli_skt.send((char*) &id_client, 4);

	//si seleccione nuevo juego
	if (id_client == 1) {
		//creo el juego
		//hardcodeado cant jugadores
		j = new juego(1, DEATHMATCH, 0);
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
		if (juegos.size() > 0){ //si hay juegos
			j = juegos[0];
			j->clientJoin(id_client, &cli_skt);
			//espero a que todos esten listos
			while (!j->readyToStart() && !end_game){
				usleep(200000);
			}
			if (end_game) return;
		} else {
			return; //si no hay juegos salgo
		}
		
	}
	
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
