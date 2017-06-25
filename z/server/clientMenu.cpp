#include "clientMenu.h"
#include <iostream>

clientMenu::clientMenu(int cli_id, tSocket &skt, gameList &gl, juego *j): 
cli_id(cli_id), skt(skt), gl(gl), j(j){}


///SE ENCARAGRIA DE LA SELECCION EN EL CLIETN MANAGER
/// NO ESTA TERMINADO, N0 USAR !!!!!!!!!!!!!!!!!!!!!111
int clientMenu::gameSelection(){
	serverProtocol prot(skt);
	int code = -1;
	skt.receive((char*)&code, 4);
	code = ntohl(code);

	if (code == CREATE_GAME) {
		//envio confirmacion
		prot.sendOKConfimation();

		//recibo datos
		int cant_p = -1;
		skt.receive((char*)&cant_p, 4);
		cant_p = ntohl(cant_p);

		int type_game = -1;
		skt.receive((char*)&type_game, 4);
		type_game = ntohl(type_game);

		int teams = -1;
		skt.receive((char*)&teams, 4);
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
		j = new juego(cli_id, cant_p, type_game, teams2, "nothing");
		j->clientJoin(cli_id, &skt, 1);
		//pusheo en el vector
		gl.push_back(j);

		//envio confirmacion
		prot.sendOKConfimation();


		//espero hasta que esten todos listos
		while (!j->readyToStart()){
			usleep(200000);
		}
		//si sali del loop porque se acaba el juego, salgo del manager
		//if (end_game) return -1;


		//que el juego envie datos iniciales
		j->sendInit();

		//empiezo el juego
		j->start();
		return 0;

	}
	if (code == JOIN_GAME){ //si seleccione unirme

		//envio confirmacion
		prot.sendOKConfimation();


		
		int cant_games;
		std::vector<int> des;
		gl.descriptionGames(des, cant_games);
		
		//envio cant juegos
		cant_games = htonl(gl.size());
		skt.send((char*)&cant_games, 4);
		
		//loop envio descripcion de juegos
		for (auto it = des.begin(); it != des.end(); ++it){
			int i = (*it);
			i = htonl(i);
			skt.send((char*)&i, 4);
		}
		
		//recibir codigo
		//mientras el socket siga vivo
		int s = 1;
		while (s > 0) {
			
			//recibo numero de creador y de equipo
			int g_to_join = 0;
			s = skt.receive((char*)&g_to_join, 4);
			g_to_join = ntohl(g_to_join);
			int team_to_join = 0;
			s = skt.receive((char*)&team_to_join, 4);
			team_to_join = ntohl(team_to_join);
			std::cout << "g_to join: "  << g_to_join << std::endl;
			std::cout << "team_to_join: "  << team_to_join << std::endl;

			//intento unirme al juego
			int joineo = gl.joinGame(cli_id, &skt, &j, g_to_join, team_to_join);
			
			//SI JOINEO manda 0 al cliente, sale con codigo 0
			//SI NO JOINE manda 1
			if (0 == joineo) {
				prot.sendOKConfimation();
				
				//espero a que todos esten listos
				while (!j->readyToStart()){
					usleep(200000);
				}
				
				//si hubo error salgo
				//if (end_game) return -1;
				return 0;
			} else {
				//envio que salio mal
				std::cout << "no joineo: " << std::endl;
				int confirm = htonl(-1);
				s = skt.send((char*)&confirm, 4);
			}
		}
		
		if (s <= 0) return -1;

	}
	
	int confirm = htonl(1);
	skt.send((char*)&confirm, 4);
	return 1;
}