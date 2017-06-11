#include <iostream>
#include "TClient_receive.h"
#include "Unit.h"
#include "Protocol.h"

TClient_receive::TClient_receive(tSocket &s, Game_map &game_map,Units_Protected &u, Factory_Units &f, bool &done, bool &r, int &id):
        socket(s),game_map(game_map),units(u), factory(f), done(done), running(r), id_client(id)  {}

TClient_receive::~TClient_receive() {}

void TClient_receive::run() {

    Protocol protocol_client_server(socket,units,game_map,factory);
    id_client = protocol_client_server.receive_id_client();
    protocol_client_server.create_map();
    protocol_client_server.set_units_game();

    done = false;
    //protocol_client_server.attackUnitCS(1, 2);

    while (running){
       protocol_client_server.process_message();
        //Agregar intervalo de tiempo

    }

}

void TClient_receive::stop() {
    this->socket.shutdown(SHUT_RD);
}
