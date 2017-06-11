#ifndef Z_PROTOCOL_H
#define Z_PROTOCOL_H


#include "../common/Socket.h"
#include "Units_Protected.h"
#include "Game_map.h"
#include "Factory_Units.h"

class Protocol {
private:
    tSocket &socket;
    Units_Protected &units;
    Game_map &game_map;
    Factory_Units &factory;

public:
    Protocol(tSocket &s, Units_Protected &u, Game_map &g, Factory_Units &f);
    ~Protocol();
    int receive_id_client();
    void moveUnitCS(int cod_unit, int posX, int posY);
    void attackUnitCS(int cod_unit, int cod_objective);
    void create_map();
    void set_units_game();
    void confirm_server(); // Esto es re turbio pero por ahora lo usamos asi que va al protocolo
    void process_message();


};


#endif //Z_PROTOCOL_H
