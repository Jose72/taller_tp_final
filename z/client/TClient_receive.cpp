#include "TClient_receive.h"

TClient_receive::TClient_receive(tSocket &s, Game_map &game_map): socket(s),game_map(game_map) {}

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
    int confirm = 0;
    socket.send((char*)&confirm,4);

}