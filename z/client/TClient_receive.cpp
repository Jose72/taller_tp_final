#include <iostream>
#include "TClient_receive.h"
#include "Unit.h"

TClient_receive::TClient_receive(tSocket &s, Game_map &game_map,Units_Protected &u, Factory_Units &f, bool &done, bool &r):
        socket(s),game_map(game_map),units(u), factory(f), done(done), running(r) {}

TClient_receive::~TClient_receive() {}

void TClient_receive::run() {

    int tamanio_map;
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
                units.add(grunt);
                break;
        }

    }
    done = false;

    int confirm = 280;
    socket.send((char*)&confirm,4);
    socket.send((char*)&confirm,4);



    while (running){
        int posX;
        int posY;
        socket.receive((char*)&posX,4);
        if (posX == -1) return;
        socket.receive((char*)&posY,4);
        if (posY == -1) return;
        units[0]->set_pos(posX,posY);
        std::cout << "x: "<< posX << std::endl;
        std::cout << "y: "<< posY << std::endl;

    }
}

void TClient_receive::stop() {
    this->socket.shutdown(SHUT_RD);
}
