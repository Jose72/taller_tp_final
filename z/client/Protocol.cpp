#include <iostream>
#include "Protocol.h"
#define CODE_MOVE_UNIT 0
#define CODE_ATTACK 1
#define CODE_SET_POS 1
#define CODE_SET_ATTACK 2
#define CODE_CREATE_UNIT 3
Protocol::Protocol(tSocket &s, Units_Protected &u, Game_map &g, Factory_Units &f):
        socket(s), units(u), game_map(g),factory(f) {}

Protocol::~Protocol() {}


void Protocol::moveUnitCS(int cod_unit, int posX, int posY) {
    std::cout << "cod unit: " << cod_unit << " x: " << posX << " y: " << posY << "\n";
    int CO_to_send = htonl(CODE_MOVE_UNIT);
    int CU_to_send = htonl(cod_unit);
    int PX_to_send = htonl(posX);
    int PY_to_send = htonl((posY));
    socket.send((char*) &CO_to_send,sizeof(int));
    //std::cout << "cod op: " << CODE_MOVE_UNIT <<"\n";
    socket.send((char*) &CU_to_send,sizeof(int));
    //std::cout << "cod unit: " << cod_unit << "\n";
    socket.send((char*) &PX_to_send,sizeof(int));
    //std::cout << " x: " << posX << "\n";
    socket.send((char*) &PY_to_send,sizeof(int));
    //std::cout <<" y: " << posY << "\n";
}

void Protocol::attackUnitCS(int cod_unit, int cod_objective) {
    int CO_to_send = htonl(CODE_ATTACK);
    int CU_to_send = htonl(cod_unit);
    int O_to_send = htonl(cod_objective);
    socket.send((char*) &CO_to_send,sizeof(int));
    socket.send((char*) &CU_to_send,sizeof(int));
    socket.send((char*) &O_to_send,sizeof(int));
    socket.send((char*) &O_to_send,sizeof(int));
}

void Protocol::create_map() {
    int tamanio_map;
    socket.receive((char*)&tamanio_map,4);
    int tamanio_map_SC = ntohl(tamanio_map);
    std::cout<< tamanio_map_SC << "\n";
    for (int i = 0; i <tamanio_map_SC ; ++i) {
        int tile;
        socket.receive((char*)&tile,4);
        int tile_SC = ntohl(tile);
        std::cout<< tile_SC <<"\n";
        game_map.add_tile(tile_SC);
    }
}

void Protocol::set_units_game() {
    int cant_unit;
    socket.receive((char*)&cant_unit,4);
    int cant_unit_SC = ntohl(cant_unit);
    for (int i = 0; i <cant_unit_SC ; ++i) {
        int unit_code_config;
        int unit_code;
        int owner;
        int posX;
        int posY;
        socket.receive((char*)&unit_code,4);
        int unit_code_SC = ntohl(unit_code);
        std::cout<< unit_code_SC << "\n";
        socket.receive((char*)&unit_code_config,4);
        int unit_code_config_SC = ntohl(unit_code_config);
        std::cout << unit_code_config_SC <<"\n";
        socket.receive((char*)&owner,4);
        int owner_SC = ntohl(owner);
        socket.receive((char*)&posX,4);
        int posX_SC = ntohl(posX);
        socket.receive((char*)&posY,4);
        int posY_SC = ntohl(posY);
        //AGREGAR SWITCH
        switch (unit_code_config_SC){
            case 0:
            std::cout <<"Se crea un grunt"<< "\n";
                Unit* grunt = factory.createUnit(BLUE_GRUNT,unit_code_SC,posX_SC,posY_SC);
                units.add(unit_code_SC,grunt);
                break;
        }

    }
}

void Protocol::confirm_server() {
    int confirm = 280;
    int confirm_CS = htonl(confirm);
    socket.send((char*)&confirm_CS,4);
    socket.send((char*)&confirm_CS,4);
}

void Protocol::process_message() {
    int cod_act;
    socket.receive((char*)&cod_act,4);
    int cod_act_SC = ntohl(cod_act);


    int cod_unit;
    socket.receive((char*)&cod_unit,4);
    int cod_unit_SC = ntohl(cod_unit);
    std::cout<< cod_act_SC <<"\n";

    int cod_unit_owner;
    socket.receive((char*)&cod_unit_owner,4);
    int cod_unit_owner_SC = ntohl(cod_unit_owner);

    int message4;
    socket.receive((char*)&message4,4);
    int message4_SC = ntohl(message4);

    int posX;
    socket.receive((char*)&posX,4);
    int posX_SC = ntohl(posX);

    int posY;
    socket.receive((char*)&posY,4);
    int posY_SC = ntohl(posY);

    if(units[cod_unit_SC]->get_state() != DEAD1) {
        switch (cod_act_SC) {
            case CODE_SET_POS:
                units[cod_unit_SC]->set_state(MOVING1);
                units[cod_unit_SC]->set_health(message4_SC);
                units[cod_unit_SC]->set_pos(posX_SC, posY_SC);
                std::cout << "x: " << posX_SC << std::endl;
                std::cout << "y: " << posY_SC << std::endl;
                break;
            case CODE_SET_ATTACK:
                units[cod_unit_SC]->set_attack(posX_SC,posY_SC);
                units[cod_unit_SC]->set_state(ATTACKING1);
                units[cod_unit_SC]->set_health(message4_SC);
                break;
            case CODE_CREATE_UNIT:
                Unit* new_unit = factory.createUnit((FlagsUnitType)cod_unit_SC,message4_SC,posX_SC,posY_SC);
                units.add(message4_SC,new_unit);
                break;
        }
    }

    for (int i = 1; i <=units.size() ; ++i) {
        if(units[i]->get_heatlh() == 0){
            units[i]->set_state(DEAD1);
        }
    }

}
