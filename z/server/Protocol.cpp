#include "Protocol.h"
#include "Event.h"

serverProtocol::serverProtocol(tSocket &s):socket(s) {}

serverProtocol::~serverProtocol() {}

void serverProtocol::send_map(std::vector<int> &tiles) {
    int map_size = htonl(tiles.size());
    socket.send((char*) &map_size,4);

    for (unsigned int i = 0; i < tiles.size() ; ++i) {
        int tile = htonl(tiles[i]);
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
	int s;
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

	e = Event(cod_operation_CS, cod_unit_CS, posX_CS, posY_CS);
	return s;
}

int serverProtocol::sendActualization(std::map<int,unit*> &map_units){
	int units_size = htonl(map_units.size());
    socket.send((char*) &units_size,4);
    for (auto it = map_units.begin(); it != map_units.end() ; ++it) {
		//codigo de estado
		int state_code = htonl(it->second->getState());
        socket.send((char*) &state_code,sizeof(int));
		//codigo unico de unidad en el juego
        int game_unit_id = htonl(it->first);
        socket.send((char*) &game_unit_id,sizeof(int));
		/*
		//codigo de unidad
		int unit_id = htonl(it->second->getUnitId());
        socket.send((char*) &unit_id,sizeof(int));
		*/
		//dueño de la unidad
        int owner_id = htonl(it->second->getOwner());
        socket.send((char*) &owner_id,sizeof(int));
		//vida de la unidad
		int health = htonl(it->second->getHealth());
        socket.send((char*) &health,sizeof(int));
		//pos x de la unidad
        int posX = htonl(it->second->getX());
        socket.send((char*) &posX,sizeof(int));
		//pos y de la unidad
        int posY = htonl(it->second->getY());
        socket.send((char*) &posY, sizeof(int));
    }
	return 0;
}