#ifndef Z_PROTOCOL_H
#define Z_PROTOCOL_H

#include <vector>
#include <map>
#include "../common/Socket.h"
#include "unit.h"

class Protocol {
private:
    tSocket &socket;
    //ACA PONE OTRAS COSAS SI LAS NECESITAS

public:
    Protocol(tSocket &s);
    ~Protocol();

    //SIGO LO QUE ESTA EN EL DOC, COMO LO PROCESAS Y ESO FIJATE VOS

    //ENVIAR
    void set_map(std::vector<int> &tiles);
    void set_units_game(std::map<int,unit*> &map_units);
    void confirm_client(); // Esto es re turbio pero por ahora lo usamos asi que va al protocolo
    void procces_message();


};


#endif //Z_PROTOCOL_H
