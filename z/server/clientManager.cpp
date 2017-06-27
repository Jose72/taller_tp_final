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
std::string &map_folder, std::string &unit_info_path): 
id_client(id), cli_skt(std::move(cli_s)), 
juegos(jgs), map_folder(map_folder), unit_info_path(unit_info_path), 
end_game(false), j(nullptr), ended(false) {}


bool tClientManager::readyToClean(){
	return ended;
}

int tClientManager::gameSelection(){
	serverProtocol prot(cli_skt);

	//recibo el codigo
	int code = -1;
	prot.receiveSelectionCode(code);

	if (code == CREATE_GAME) {
        //envio confirmacion
        prot.sendOKConfimation();

        //recibo datos
        int cant_p = -1;
        int type_game = -1;
        int teams = -1;
        prot.receiveCreateGameData(cant_p, type_game, teams);

        //si la cant de jugadores es menor o igual a 1 da error
        if (cant_p <= 1) {
            return 1;
        }

        //creo el juego
        //harcodeo

        //si es deathmanth -> equipos = jugadores
        int teams2 = teams;
        if (type_game == DEATHMATCH) {
            teams2 = cant_p;
        } else {
            //sino tienen que ser equipos parejos
            // 1 < cant equipos < 4
            if ((cant_p % teams) != 0 || teams <= 1 || teams > 4) {
                int confirm = htonl(1);
                cli_skt.send((char *) &confirm, 4);
                return 1;
            }
        }

        //////////////////////////////////////////////////////////
        //PARTE DE SELECCION DE MAPAS


        //envio confirmacion

        prot.sendOKConfimation();

        MapLoader m_loader(map_folder);
        m_loader.loadListData();
        std::vector<dataMap> maps_info = m_loader.mapsForTeams(teams2);
        prot.sendMapsInfo(maps_info);

        //recibo nombre de mapa
        std::string mapa_nombre;
        //si recibi bien
        if (0 < prot.receiveMapName(mapa_nombre) && mapa_nombre != "") {
			
            //creo el nuevo juego
            j = new juego(id_client, cant_p, type_game, teams2, mapa_nombre, map_folder, unit_info_path);
            j->clientJoin(id_client, &cli_skt, 1);
            //pusheo en el vector de juegos, para que quede listado
            juegos.push_back(j);

            //empiezo el juego
            j->start();
            return 0;
        }
        return -1;

		///////////////////////FIN-CREATE-GAME////////////////////////////////7
	}
	if (code == JOIN_GAME){ //si seleccione unirme
		//envio confirmacion
		prot.sendOKConfimation();

		//obtengo la descripcion de los juegos
		int cant_games;
		std::vector<int> des;
		juegos.descriptionGames(des, cant_games);

        //envio descripcion  de los juegos
        prot.sendGamesDescription(des, cant_games);

		//recibir codigo
		//mientras el socket siga vivo (y no me hagan stop en el manager)
		//loopeo hasta que joinee a la aprtida
		int s = 1;
		while (s > 0 && !end_game) {
			
			//recibo numero de creador y de equipo
			int g_to_join = 0;
            int team_to_join = 0;
            prot.receiveGameToJoin(g_to_join,team_to_join);
            /*
			s = cli_skt.receive((char*)&g_to_join, 4);
			g_to_join = ntohl(g_to_join);

			s = cli_skt.receive((char*)&team_to_join, 4);
			team_to_join = ntohl(team_to_join);
            */
			//intento unirme al juego
			int joineo = juegos.joinGame(id_client, &cli_skt, &j, g_to_join, team_to_join);
			
			//SI JOINEO manda 0 al cliente, sale con codigo 0
			//SI NO JOINE manda 1
			if (0 == joineo) {
				prot.sendOKConfimation();
				return 0;
			} else {
				//envio que salio mal
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
		end_game = true;
        cli_skt.shutdown(SHUT_RDWR);
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
	
	int s = 1;
	while (s > 0 && !end_game) {
		Event e;
		s = protocolo.receive_event(e);
		if (s > 0) {

			//el juego tiene el mutex
			j->take_event(e);
		}
	}

	ended = true;
	return;
}
