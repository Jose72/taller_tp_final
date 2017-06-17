#include <iostream>
#include "Protocol.h"
#include "Event.h"

serverProtocol::serverProtocol(tSocket &s):socket(s) {}

serverProtocol::~serverProtocol() {}


void serverProtocol::send_id_client(int id_client) {
    int id = htonl(id_client);
    socket.send((char*)&id, 4);
}

void serverProtocol::send_map(int * map_s, unsigned int size) {
    int map_size = htonl(size);
    socket.send((char*) &map_size,4);


    for (unsigned int i = 0; i < size ; ++i) {
        int tile = htonl(*(map_s+ i));
        socket.send((char*) &tile,4);
        //std::cout<< "map size: "<<*(map_s+ i) << "\n";
    }
}

void serverProtocol::send_map(std::vector<int> &map_s) {
    int map_size = htonl(map_s.size());
    socket.send((char*) &map_size,4);

    for (int i = 0; i <map_s.size() ; ++i) {
        int tile = htonl(map_s[i]);
        socket.send((char*) &tile,4);
    }
}

void serverProtocol::send_units_game(std::map<int, unit *> &map_units) {
    int units_size = htonl(map_units.size());
    socket.send((char*) &units_size,4);
    for (auto it = map_units.begin(); it != map_units.end() ; ++it) {
        int game_unit_id = htonl(it->first);
        socket.send((char*) &game_unit_id,sizeof(int));

        int unit_id = htonl(it->second->getUnitId());
        socket.send((char*) &unit_id,sizeof(int));

        int owner_id = htonl(it->second->getOwner());
        socket.send((char*) &owner_id,sizeof(int));

        int posX = htonl(it->second->getX());
        socket.send((char*) &posX,sizeof(int));

        int posY = htonl(it->second->getY());
        socket.send((char*) &posY, sizeof(int));
    }
}

void serverProtocol::confirm_client() {
    int confirmation;
    socket.receive((char*)&confirmation,sizeof(int));
    socket.receive((char*)&confirmation,sizeof(int));
}

int serverProtocol::receive_event(Event &e) {
    std::cout << "recibe event" << std::endl;
	int s = 1;
    int cod_operation;
    s = socket.receive((char*)&cod_operation,sizeof(int));
    int cod_operation_CS = ntohl(cod_operation);

    int cod_unit;
    s = socket.receive((char*)&cod_unit,sizeof(int));
    int cod_unit_CS = ntohl(cod_unit);

    int posX;
    s = socket.receive((char*)&posX,sizeof(int));
    int posX_CS = ntohl(posX);

    int posY;
    s = socket.receive((char*)&posY,sizeof(int));
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
	s = socket.send((char*) &state_code,sizeof(int));
	//winner
	int winner = htonl(w);
	s = socket.send((char*) &winner,sizeof(int));
	//basura
	int trash = htonl(0);
	s = socket.send((char*) &trash,sizeof(int));
	s = socket.send((char*) &trash,sizeof(int));
	s = socket.send((char*) &trash,sizeof(int));
	s = socket.send((char*) &trash,sizeof(int));
	s = socket.send((char*) &trash,sizeof(int));
    //std::cout << "finish act - s: " << s << std::endl;
	return s;
}

int serverProtocol::sendUpdateTechLvl(int tech_lvl){
	int s = 1;
	int code = 35;
	//codigo de actualizacion
	int state_code = htonl(code);
	s = socket.send((char*) &state_code,sizeof(int));
	//tech lvl
	int tech_l = htonl(tech_lvl);
	s = socket.send((char*) &tech_l,sizeof(int));
	//basura
	int trash = htonl(0);
	socket.send((char*) &trash,sizeof(int));
	s = socket.send((char*) &trash,sizeof(int));
	s = socket.send((char*) &trash,sizeof(int));
	s = socket.send((char*) &trash,sizeof(int));
	s = socket.send((char*) &trash, sizeof(int));
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
        s = socket.send((char*) &state_code,sizeof(int));
		//codigo unico de unidad en el juego
        int game_unit_id = htonl(it->first);
        s = socket.send((char*) &game_unit_id,sizeof(int));
		//codigo de unidad
		int unit_id = htonl(it->second->getUnitId());
        s = socket.send((char*) &unit_id,sizeof(int));
		//dueño de la unidad
        int owner_id = htonl(it->second->getOwner());
		s = socket.send((char*) &owner_id,sizeof(int));
		//vida de la unidad
		int health = htonl(it->second->getHealth());
        s = socket.send((char*) &health,sizeof(int));
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
