#ifndef SERVERPROTOCOL_H
#define SERVERPROTOCOL_H

#include <vector>
#include <map>
#include "../common/Socket.h"
#include "unit.h"
#include "Event.h"

class serverProtocol {
private:
    tSocket &socket;
    //ACA PONE OTRAS COSAS SI LAS NECESITAS

public:
    serverProtocol(tSocket &s);
    ~serverProtocol();

    //SIGO LO QUE ESTA EN EL DOC, COMO LO PROCESAS Y ESO FIJATE VOS

    //ENVIAR
    void send_map(std::vector<int> &tiles);
    void send_units_game(std::map<int,unit*> &map_units);
    void confirm_client(); // Esto es re turbio pero por ahora lo usamos asi que va al protocolo
	int sendActualization(std::map<int,unit*> &map_units);
    int receive_event(Event &e);


};


#endif //Z_PROTOCOL_H