#include <iostream>
#include "TClient_receive.h"
#include "Unit.h"
#include "Protocol.h"

TClient_receive::TClient_receive(tSocket &s,
                                 Game_map &game_map,
                                 Units_Protected &u,
                                 Factory_Units &f,
                                 bool &done,
                                 bool &r,
                                 int &id,
                                 int &dimensions,
                                 int &posXI,
                                 int &posYI,
                                 TechLevelProtected &tech,
                                 WinnerProtected &winner,
                                SoundManager &soundManager):
        socket(s),
        game_map(game_map),
        units(u),
        factory(f),
        done(done),
        running(r),
        id_client(id),
        dimensions(dimensions),
        posXI(posXI),
        posYI(posYI),
        techLevel(tech),
        winner(winner),
        soundManager(soundManager)  {}

TClient_receive::~TClient_receive() {}

void TClient_receive::run() {
    done = true;
    Protocol protocol_client_server(socket,units,
                                    game_map,factory,
                                    techLevel, winner,soundManager);
    protocol_client_server.mapDataInitial(id_client,dimensions,posXI,posYI);

    protocol_client_server.create_map();
    protocol_client_server.set_units_game();

    done = false;


    while (running){
       protocol_client_server.process_message();
    }

}

void TClient_receive::stop() {
    this->socket.shutdown(SHUT_RD);
}
