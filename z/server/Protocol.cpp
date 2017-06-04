#include "Protocol.h"


Protocol::Protocol(tSocket &s):socket(s) {}

Protocol::~Protocol() {}

void Protocol::set_map(std::vector<int> &tiles) {
    int map_size = htonl(tiles.size());
    socket.send((char*) &map_size,4);

    for (unsigned int i = 0; i < tiles.size() ; ++i) {
        int tile = htonl(tiles[i]);
        socket.send((char*) &tile,4);
    }
}

void Protocol::set_units_game(std::map<int, unit *> &map_units) {
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

void Protocol::confirm_client() {
    int confirmation;
    socket.receive((char*)&confirmation,sizeof(int));
    socket.receive((char*)&confirmation,sizeof(int));
}

void Protocol::procces_message() {
    int cod_operation;
    socket.receive((char*)&cod_operation,sizeof(int));
    int cod_operation_CS = ntohl(cod_operation);

    int cod_unit;
    socket.receive((char*)&cod_unit,sizeof(int));
    int cod_unit_CS = ntohl(cod_unit);

    int posX;
    socket.receive((char*)&posX,sizeof(int));
    int posX_CS = ntohl(posX);

    int posY;
    socket.receive((char*)&posY,sizeof(int));
    int posY_CS = ntohl(posY_CS);

    //DESPUES FALTARIA PROCESAR ESTO Y DEMAS
}

