#include <iostream>
#include "Protocol.h"
#define CODE_MOVE_UNIT 0
#define CODE_ATTACK 1
#define CODE_SET_POS 1
#define CODE_SET_ATTACK 2
#define CODE_CREATE_UNIT 2
#define CODE_DIE 5
#define CODE_STAND 6
#define CODE_CHECKING_CAPTURE 8
#define CODE_DESTROYED 10
#define CODE_CHANGE_TECH_LEVEL 35
#define CODE_END_GAME 40
Protocol::Protocol(tSocket &s, Units_Protected &u, Game_map &g, Factory_Units &f, TechLevelProtected &tech):
        socket(s), units(u), game_map(g),factory(f), techLevel(tech) {}

Protocol::~Protocol() {}

int Protocol::receive_id_client() {
    int id_c;
    socket.receive((char*)&id_c,4);
    int id_c_SC =ntohl(id_c);
    return id_c_SC;
}

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
    //std::cout<< tamanio_map_SC << "\n";
    for (int i = 0; i <tamanio_map_SC ; ++i) {
        int tile;
        socket.receive((char*)&tile,4);
        int tile_SC = ntohl(tile);
        //std::cout<< tile_SC <<"\n";
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
        //std::cout << unit_code_config_SC <<"\n";
        socket.receive((char*)&owner,4);
        int owner_SC = ntohl(owner);
        socket.receive((char*)&posX,4);
        int posX_SC = ntohl(posX);
        socket.receive((char*)&posY,4);
        int posY_SC = ntohl(posY);
        //AGREGAR SWITCH
        units.createIsNotExist(unit_code_SC,unit_code_config_SC,owner_SC,posX_SC,posY_SC,factory);

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

    int unit_type;
    socket.receive((char*)&unit_type,4);
    int unit_type_SC = ntohl(unit_type);


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

    translate_message(cod_act_SC,
                      cod_unit_SC,
                      unit_type_SC,
                      cod_unit_owner_SC,
                      message4_SC,
                      posX_SC,
                      posY_SC);

}

void Protocol::create_unit(int idCreator, int idCreation) {
    int CO_to_send = htonl(CODE_CREATE_UNIT);
    int idCreator_to_send = htonl(idCreator);
    int idCreation_to_send = htonl(idCreation);
    int extra_to_send = htonl(0);
    socket.send((char*) &CO_to_send,sizeof(int));
    socket.send((char*) &idCreator_to_send,sizeof(int));
    socket.send((char*) &idCreation_to_send,sizeof(int));
    socket.send((char*) &extra_to_send,sizeof(int));
}

void Protocol::translate_message(int update, int unitCode, int unitType, int unitOwner, int health, int posX,
                                 int posY) {
    if (update == CODE_END_GAME) {
        units.endGame(unitCode);
    } else if (update == CODE_CHANGE_TECH_LEVEL) {
        techLevel.setTechLevel(unitCode);
    } else {
        units.createIsNotExist(unitCode, unitType, unitOwner, posX, posY, factory);
        if (units[unitCode]->get_state() != DEAD1) {
            switch (update) {
                case CODE_SET_POS:
                    units[unitCode]->set_state(MOVING1);
                    units[unitCode]->set_health(health);
                    units[unitCode]->set_pos(posX, posY);
                    break;
                case CODE_SET_ATTACK:
                    units[unitCode]->set_attack(posX, posY);
                    units[unitCode]->set_state(ATTACKING1);
                    units[unitCode]->set_health(health);
                    break;
                case CODE_DIE:
                    units[unitCode]->set_state(DEAD1);
                    break;
                case CODE_STAND:
                    units[unitCode]->set_state(DRINKING);
                    break;
                case CODE_CHECKING_CAPTURE:
                    units[unitCode]->set_owner(unitOwner);
                    break;
                case CODE_DESTROYED:
                    units[unitCode]->set_state(DESTROYED1);
            }
        }
    }
}

