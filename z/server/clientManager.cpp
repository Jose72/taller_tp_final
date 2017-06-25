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
#include "MapLoader.h"

#include "juego.h"

tClientManager::tClientManager(int id, tSocket cli_s, gameList &jgs, 
std::mutex &manager_m): id_client(id), cli_skt(std::move(cli_s)), 
manager_m(manager_m), juegos(jgs), end_game(false), j(nullptr), ended(false) {}


bool tClientManager::readyToClean(){
	return ended;
}

int tClientManager::gameSelection(){
	serverProtocol prot(cli_skt);

	//recibo el codigo
	int code = -1;
	cli_skt.receive((char*)&code, 4);
	code = ntohl(code);

	if (code == CREATE_GAME) {
		//envio confirmacion
		prot.sendOKConfimation();

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
			// 1 < cant equipos < 4
			if ((cant_p % teams) != 0 || teams <= 1 || teams > 4) return 1;
		}
		
		//////////////////////////////////////////////////////////
		//PARTE DE SELECCION DE MAPAS


        //envio confirmacion

        prot.sendOKConfimation();

		MapLoader m_loader;
		m_loader.loadListData();
		std::vector<dataMap> maps_info = m_loader.mapsForTeams(teams2);
		prot.sendMapsInfo(maps_info);



		//recibo tamanio del nombre
		int name_size = 0;
		cli_skt.receive((char*)&name_size, 4);
		name_size = ntohl(name_size);
		//recibo el nombre
		char buff[100] = {'\0'};
		cli_skt.receive((char*)&buff[0], name_size);
		std::string mapa_nombre(&buff[0]);

		std::cout << mapa_nombre << std::endl;
		
		
		///////////////////////////////////////////////////////////
		//*nombre del mapa harcodeado (arreglar cuando este la seleccion de mapas)
		//creo el nuevo juego
		j = new juego(id_client, cant_p, type_game, teams2, "nothing");
		j->clientJoin(id_client, &cli_skt, 1);
		//pusheo en el vector de juegos, para que quede listado
		juegos.push_back(j);

		//envio confirmacion
		//prot.sendOKConfimation(); //cliente no espera confirmacion despues de elegir el mapa

		//empiezo el juego
		j->start();
		return 0;
		
		///////////////////////FIN-CREATE-GAME////////////////////////////////7
	}
	if (code == JOIN_GAME){ //si seleccione unirme
		//envio confirmacion
		prot.sendOKConfimation();
		//obtengo la descripcion de los juegos
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
		//mientras el socket siga vivo (y no me hagan stop en el manager)
		int s = 1;
		while (s > 0 && !end_game) {
			
			//recibo numero de creador y de equipo
			int g_to_join = 0;
			s = cli_skt.receive((char*)&g_to_join, 4);
			g_to_join = ntohl(g_to_join);
			int team_to_join = 0;
			s = cli_skt.receive((char*)&team_to_join, 4);
			team_to_join = ntohl(team_to_join);
			std::cout << "g_to join: "  << g_to_join << std::endl;
			std::cout << "team_to_join: "  << team_to_join << std::endl;

			//intento unirme al juego
			int joineo = juegos.joinGame(id_client, &cli_skt, &j, g_to_join, team_to_join);
			
			//SI JOINEO manda 0 al cliente, sale con codigo 0
			//SI NO JOINE manda 1
			if (0 == joineo) {
				prot.sendOKConfimation();
				return 0;
			} else {
				//envio que salio mal
				std::cout << "no joineo: " << std::endl;
				int confirm = htonl(-1);
				s = cli_skt.send((char*)&confirm, 4);
			}
		}
		
		///////////////////////FIN-JOIN-GAME////////////////////////////////7
		
		if (s <= 0 || end_game) return -1;

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
	serverProtocol protocolo(cli_skt);

	//enviar id cliente;
	protocolo.send_id_client(id_client);
	
	///////////////////////////////////////////////////////////
	////SELECCION DE JUEGO
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
	
	//std::cout << "empezo client: " << id_client << std::endl;	
	
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
