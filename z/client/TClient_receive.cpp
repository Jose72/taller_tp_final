#include <iostream>
#include "TClient_receive.h"
#include "Unit.h"

TClient_receive::TClient_receive(tSocket &s, Game_map &game_map,std::vector<Unit*> &u, Factory_Units &f):
        socket(s),game_map(game_map),units(u), factory(f) {}

TClient_receive::~TClient_receive() {}

void TClient_receive::run() {
    int tamanio_map;
    bool r = true;
    socket.receive((char*)&tamanio_map,4);
    //network to host
    for (int i = 0; i <tamanio_map ; ++i) {
        int tile;
        socket.receive((char*)&tile,4);
        game_map.add_tile(tile);
    }
    int cant_unit;
    socket.receive((char*)&cant_unit,4);
    for (int i = 0; i <cant_unit ; ++i) {
        int unit_code;
        int posX;
        int posY;
        socket.receive((char*)&unit_code,4);
        socket.receive((char*)&posX,4);
        socket.receive((char*)&posY,4);
        switch (unit_code){
            case 0:
                Unit* grunt = factory.createUnit(BLUE_GRUNT,posX,posY);
                units.push_back(grunt);
                break;
        }

    }
    int confirm = 120;
    socket.send((char*)&confirm,4);
    socket.send((char*)&confirm,4);

    while (r){
        int posX;
        int posY;
        socket.receive((char*)&posX,4);
        socket.receive((char*)&posY,4);
       // units[0]->set_pos(posX,posY);
        std::cout << posX;

    }
}

void TClient_receive::stop() {
    this->socket.shutdown(SHUT_RDWR);
}