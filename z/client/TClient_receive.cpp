#include <iostream>
#include "TClient_receive.h"
#include "Unit.h"
#include "Protocol.h"

TClient_receive::TClient_receive(tSocket &s,
                                 Game_map &game_map,
                                 Units_Protected &u,
                                 Factory_Units &f,
                                 bool &done, bool &r, int &id,
                                 TechLevelProtected &tech,
                                 WinnerProtected &winner,
                                SoundManager &soundManager):
        socket(s),game_map(game_map),units(u), factory(f), done(done), running(r), id_client(id),techLevel(tech),winner(winner),soundManager(soundManager)  {}

TClient_receive::~TClient_receive() {}

void TClient_receive::run() {
    done = true;
    Protocol protocol_client_server(socket,units,game_map,factory, techLevel, winner,soundManager);


    /////////////////////////
    //RECIBO NUMERO DE TEAM
    int team_n;
    socket.receive((char*) &team_n, 4);
    team_n = ntohl(team_n);
    id_client = team_n;
    /////////////////////////
    //recibo dimension de mapa
    int map_dim;
    socket.receive((char*) &map_dim, 4);
    map_dim = ntohl(map_dim);
    std::cout << map_dim << std::endl;
    /////////////////////////
    //recibo pos inicial
    int x_inicial;
    int y_inicial;
    socket.receive((char*) &x_inicial, 4);
    socket.receive((char*) &y_inicial, 4);
    x_inicial = ntohl(x_inicial);
    y_inicial = ntohl(y_inicial);
    std::cout << "x_initial: "<< x_inicial << std::endl;
    std::cout << "y_initial: "<< x_inicial << std::endl;
    /////////////////////////

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
