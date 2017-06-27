#include <iostream>
#include "Protocol.h"
#include "Event.h"

#define INT_SIZE 4

serverProtocol::serverProtocol(tSocket &s):socket(s) {}

serverProtocol::~serverProtocol() {}

//envio de la id al cliente
void serverProtocol::send_id_client(int id_client) {
    int id = htonl(id_client);
    socket.send((char*)&id, INT_SIZE);
}


//envio de mapa a los jugadores
void serverProtocol::send_map(int * map_s, unsigned int size) {
    int map_size = htonl(size);
    socket.send((char*) &map_size, INT_SIZE);

    for (unsigned int i = 0; i < size ; ++i) {
        int tile = htonl(*(map_s+ i));
        socket.send((char*) &tile, INT_SIZE);
    }
}

//envio de mapa a los jugadores
void serverProtocol::send_map(std::vector<int> &map_s) {
    int map_size = htonl(map_s.size());
    socket.send((char*) &map_size, INT_SIZE);

    for (unsigned int i = 0; i < map_s.size() ; ++i) {
        int tile = htonl(map_s[i]);
        socket.send((char*) &tile, INT_SIZE);
    }
}

//envio del numero de equipo a los jugadores
void serverProtocol::send_team_number(int t){
	int team_n = htonl(t);
	socket.send((char*) &team_n,INT_SIZE);
}

//envio de la posicion inicial a los jugadores
void serverProtocol::send_init_pos(int x, int y){
	int x_x = htonl(x);
	socket.send((char*) &x_x, INT_SIZE);
	int y_y = htonl(y);
	socket.send((char*) &y_y, INT_SIZE);
}

//codigo de confirmacion OK
int serverProtocol::sendOKConfimation(){
	int i = htonl(0);
	return socket.send((char*) &i,sizeof(int));
}

//envio de informacion de los mapas disponibles 
void serverProtocol::sendMapsInfo(std::vector<dataMap> &maps) {
	//envio cantidad de mapas
	int cant_maps = maps.size();
	cant_maps = htonl(cant_maps);
	socket.send((char*)&cant_maps, INT_SIZE);
	
	//envio la info en un loop
	for (unsigned int i = 0; i < maps.size(); ++i){
		//nombre del mapa
		std::string name = maps[i].mapName;
		int name_size = htonl(name.size());
		//envio cant de bytes y luego el string
		socket.send((char*)&name_size, INT_SIZE);
		socket.send((char*)&name[0u], name.size());
		//dimensiones
		int dim = maps[i].dimensiones;
		dim = htonl(dim);
		socket.send((char*)&dim, INT_SIZE);
		//dimensiones
		int cant_e = maps[i].cantEquipos;
		cant_e = htonl(cant_e);
		socket.send((char*)&cant_e, INT_SIZE);
	}
}

//envio de las unidades iniciales a los jugadores
void serverProtocol::send_units_game(std::map<int, unit *> &map_units) {
    int units_size = htonl(map_units.size());
    socket.send((char*) &units_size, INT_SIZE);
    for (auto it = map_units.begin(); it != map_units.end() ; ++it) {
        int game_unit_id = htonl(it->first);
        socket.send((char*) &game_unit_id, INT_SIZE);

        int unit_id = htonl(it->second->getUnitId());
        socket.send((char*) &unit_id, INT_SIZE);

        int owner_id = htonl(it->second->getOwner());
        socket.send((char*) &owner_id, INT_SIZE);

        int posX = htonl(it->second->getX());
        socket.send((char*) &posX, INT_SIZE);

        int posY = htonl(it->second->getY());
        socket.send((char*) &posY, INT_SIZE);
		

		//envia tl de la unidad (pasa saber en que estan los edificios)
		//id del conduciotr en el caso de los vehiculos
		int m = -1;
		int c = it->second->getClassId();
		switch(c){
			case BUILDING:{
				m = it->second->getTechLvl();
				break;
			}
			case VEHICLE:{
				unit *d = it->second->getDriver();
				if (d){
					m = d->getUnitId();
				}
				break;
			}
		}
		m = htonl(m);
        socket.send((char*) &m, INT_SIZE);

    }
}

//envio de la dimensiond el mapa a los jugadores
void serverProtocol::send_map_dim(int map_dim) {
    int md = htonl(map_dim);
    socket.send((char*)&md, INT_SIZE);
}


//recepcion de un evento
int serverProtocol::receive_event(Event &e) {
	int s = 0;
    int cod_operation;
    socket.receive((char*)&cod_operation, INT_SIZE);
    int cod_operation_CS = ntohl(cod_operation);

    int cod_unit;
    socket.receive((char*)&cod_unit, INT_SIZE);
    int cod_unit_CS = ntohl(cod_unit);

    int posX;
    socket.receive((char*)&posX, INT_SIZE);
    int posX_CS = ntohl(posX);

    int posY;
    s = socket.receive((char*)&posY, INT_SIZE);
    int posY_CS = ntohl(posY);

	e = Event(cod_operation_CS, cod_unit_CS, posX_CS, posY_CS);
	return s;
}


//envio de codigo de victoria con el numerod el equipo ganador
int serverProtocol::sendVictory(int w){
	int s = 0;
	int code = 40;
	//codigo de actualizacion
	int state_code = htonl(code);
	socket.send((char*) &state_code, INT_SIZE);
	//winner
	int winner = htonl(w);
	socket.send((char*) &winner, INT_SIZE);
	//basura
	int trash = htonl(0);
	socket.send((char*) &trash, INT_SIZE);
	socket.send((char*) &trash, INT_SIZE);
	socket.send((char*) &trash, INT_SIZE);
	socket.send((char*) &trash, INT_SIZE);
	socket.send((char*) &trash, INT_SIZE);
	s = socket.send((char*) &trash, INT_SIZE);
	return s;
}

//envio de las actualizaciones de las unidades
int serverProtocol::sendActualization(std::map<int,unit*> &map_units){
	//int units_size = htonl(map_units.size());
    //socket.send((char*) &units_size,4);
	int s = 0;
    for (auto it = map_units.begin(); it != map_units.end() ; ++it) {
		//codigo de estado
		int state_code = htonl(it->second->getState());
        socket.send((char*) &state_code, INT_SIZE);
		//codigo unico de unidad en el juego
        int game_unit_id = htonl(it->first);
        socket.send((char*) &game_unit_id, INT_SIZE);
		//codigo de unidad
		int unit_id = htonl(it->second->getUnitId());
        socket.send((char*) &unit_id, INT_SIZE);
		//dueño de la unidad
        int owner_id = htonl(it->second->getOwner());
		socket.send((char*) &owner_id, INT_SIZE);
		//vida de la unidad
		int health = htonl(it->second->getHealth());
        socket.send((char*) &health, INT_SIZE);


		int m = -1;
		int c = it->second->getClassId();
		switch(c){
			case BUILDING:{
				m = it->second->getTimeToCompletion();
				break;
			}
			case VEHICLE:{
				unit *d = it->second->getDriver();
				if (d){
					m = d->getUnitId();
				}
				break;
			}
		}
		m = htonl(m);
		socket.send((char*) &m, sizeof(int));

		 
		//pos x de la unidad
        int posX = htonl(it->second->getX());
        socket.send((char*) &posX,sizeof(int));
		//pos y de la unidad
        int posY = htonl(it->second->getY());
        s = socket.send((char*) &posY, sizeof(int));
    }
	
	return s;
}

//recibe el codigo para unirse a un juego o crearlo
void serverProtocol::receiveSelectionCode(int &c){
	int i;
	socket.receive((char*)&i, INT_SIZE);
	c = ntohl(i);
}

void serverProtocol::receiveCreateGameData(int &cant_p, int &type_game, int &teams){
	int i = -1;
	socket.receive((char*)&i, INT_SIZE);
	cant_p = ntohl(i);
	i = -1;
	socket.receive((char*)&i, INT_SIZE);
	type_game = ntohl(i);
	i = -1;
	socket.receive((char*)&i, INT_SIZE);
	teams = ntohl(i);
}

//recibo el nombre del mapa que selcciono el cliente
void serverProtocol::receiveMapName(std::string &map_name){
	//recibo tamanio del nombre
	int name_size = 0;
	socket.receive((char*)&name_size,INT_SIZE);
	name_size = ntohl(name_size);
	//recibo el nombre
	char buff[100] = {'\0'};
	socket.receive((char*)&buff[0], name_size);
	map_name = std::string(&buff[0]);
}

void serverProtocol::sendGamesDescription(std::vector<int> &des, int cant_j) {
	//envio cant juegos
	int cant_games = htonl(cant_j);
	socket.send((char *) &cant_games, INT_SIZE);

	//loop envio descripcion de juegos
	for (auto it = des.begin(); it != des.end(); ++it) {
		int i = (*it);
		i = htonl(i);
		socket.send((char *) &i, INT_SIZE);
	}
}

void serverProtocol::receiveGameToJoin(int &g_id, int &t) {
	int g_to_join = 0;
	socket.receive((char*)&g_to_join, 4);
	g_id = ntohl(g_to_join);
	int team_to_join = 0;
	socket.receive((char*)&team_to_join, 4);
	t = ntohl(team_to_join);
}

