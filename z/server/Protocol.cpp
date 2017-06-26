#include <iostream>
#include "Protocol.h"
#include "Event.h"

#define INT_SIZE 4

serverProtocol::serverProtocol(tSocket &s):socket(s) {}

serverProtocol::~serverProtocol() {}


void serverProtocol::send_id_client(int id_client) {
    int id = htonl(id_client);
    socket.send((char*)&id, INT_SIZE);
}


void serverProtocol::send_map(int * map_s, unsigned int size) {
    int map_size = htonl(size);
    socket.send((char*) &map_size, INT_SIZE);


    for (unsigned int i = 0; i < size ; ++i) {
        int tile = htonl(*(map_s+ i));
        socket.send((char*) &tile, INT_SIZE);
        //std::cout<< "map size: "<<*(map_s+ i) << "\n";
    }
}

void serverProtocol::send_map(std::vector<int> &map_s) {
    int map_size = htonl(map_s.size());
    socket.send((char*) &map_size, INT_SIZE);

    for (unsigned int i = 0; i < map_s.size() ; ++i) {
        int tile = htonl(map_s[i]);
        socket.send((char*) &tile, INT_SIZE);
    }
}

void serverProtocol::send_team_number(int t){
	int team_n = htonl(t);
	socket.send((char*) &team_n,INT_SIZE);
}

void serverProtocol::send_init_pos(int x, int y){
	int x_x = htonl(x);
	socket.send((char*) &x_x, INT_SIZE);
	int y_y = htonl(y);
	socket.send((char*) &y_y, INT_SIZE);
}

int serverProtocol::sendOKConfimation(){
	int i = htonl(0);
	return socket.send((char*) &i,sizeof(int));
}

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
			case(BUILDING):{
				m = it->second->getTechLvl();
				break;
			}
			case(VEHICLE):{
				unit *d = it->second->getDriver();
				if (d){
					m = d->getUnitId();
				}
				break;
			}
		}
		m = htonl(m);
        socket.send((char*) &m, sizeof(int));

    }
}

int serverProtocol::receive_event(Event &e) {
    std::cout << "recibe event" << std::endl;
	int s = 1;
    int cod_operation;
    s = socket.receive((char*)&cod_operation, INT_SIZE);
    int cod_operation_CS = ntohl(cod_operation);

    int cod_unit;
    s = socket.receive((char*)&cod_unit, INT_SIZE);
    int cod_unit_CS = ntohl(cod_unit);

    int posX;
    s = socket.receive((char*)&posX, INT_SIZE);
    int posX_CS = ntohl(posX);

    int posY;
    s = socket.receive((char*)&posY, INT_SIZE);
    int posY_CS = ntohl(posY);


    std::cout << "op_code: " << cod_operation_CS << " unit_code: " << cod_unit_CS <<
              " x_code: " << posX_CS << " y_code: " << posY_CS << std::endl;
	e = Event(cod_operation_CS, cod_unit_CS, posX_CS, posY_CS);
	return s;
}



int serverProtocol::sendVictory(int w){
	int s = 1;
	int code = 40;
	//codigo de actualizacion
	int state_code = htonl(code);
	s = socket.send((char*) &state_code, INT_SIZE);
	//winner
	int winner = htonl(w);
	s = socket.send((char*) &winner, INT_SIZE);
	//basura
	int trash = htonl(0);
	s = socket.send((char*) &trash, INT_SIZE);
	s = socket.send((char*) &trash, INT_SIZE);
	s = socket.send((char*) &trash, INT_SIZE);
	s = socket.send((char*) &trash, INT_SIZE);
	s = socket.send((char*) &trash, INT_SIZE);
	s = socket.send((char*) &trash, INT_SIZE);
    //std::cout << "finish act - s: " << s << std::endl;
	return s;
}

int serverProtocol::sendUpdateTechLvl(int tech_lvl){
	int s = 1;
	int code = 35;
	//codigo de actualizacion
	int state_code = htonl(code);
	s = socket.send((char*) &state_code, INT_SIZE);
	//tech lvl
	int tech_l = htonl(tech_lvl);
	s = socket.send((char*) &tech_l, INT_SIZE);
	//basura
	int trash = htonl(0);
	socket.send((char*) &trash, INT_SIZE);
	s = socket.send((char*) &trash, INT_SIZE);
	s = socket.send((char*) &trash, INT_SIZE);
	s = socket.send((char*) &trash, INT_SIZE);
	s = socket.send((char*) &trash, INT_SIZE);
	s = socket.send((char*) &trash, INT_SIZE);
    //std::cout << "finish act - s: " << s << std::endl;
	return s;
}


int serverProtocol::sendActualization(std::map<int,unit*> &map_units){
	//int units_size = htonl(map_units.size());
    //socket.send((char*) &units_size,4);
	int s = 1;
    for (auto it = map_units.begin(); it != map_units.end() ; ++it) {
		//codigo de estado
		int state_code = htonl(it->second->getState());
        s = socket.send((char*) &state_code, INT_SIZE);
		//codigo unico de unidad en el juego
        int game_unit_id = htonl(it->first);
        s = socket.send((char*) &game_unit_id, INT_SIZE);
		//codigo de unidad
		int unit_id = htonl(it->second->getUnitId());
        s = socket.send((char*) &unit_id, INT_SIZE);
		//dueño de la unidad
        int owner_id = htonl(it->second->getOwner());
		s = socket.send((char*) &owner_id, INT_SIZE);
		//vida de la unidad
		int health = htonl(it->second->getHealth());
        s = socket.send((char*) &health, INT_SIZE);


		int m = -1;
		int c = it->second->getClassId();
		switch(c){
			case(BUILDING):{
				m = it->second->getTimeToCompletion();
				break;
			}
				case(VEHICLE):{
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
        s = socket.send((char*) &posX,sizeof(int));
		//pos y de la unidad
        int posY = htonl(it->second->getY());
        s = socket.send((char*) &posY, sizeof(int));
    }
    //std::cout << "finish act - s: " << s << std::endl;
	return s;
}
