//
// Created by mbataglia on 06/06/17.
//

#include <vector>
#include <string>
#include <iostream>
#include "ProtocolMenu.h"

#define CODE_FETCH_GAMES 1000

ProtocolMenu::ProtocolMenu(tSocket &socket) : socket(socket) {}

std::vector<std::string> ProtocolMenu::fetchGames(){
    std::vector<std::string> vectorGames;
    /** int CO_to_send = htonl(CODE_FETCH_GAMES);
     socket.send((char*)CO_to_send,sizeof(int));

     int sizeGames;
     socket.receive((char*)&sizeGames,4);
     int sizeGames_SC = ntohl(sizeGames);

     char games[sizeGames_SC];
     socket.receive((char*)&games,sizeGames_SC);

     std::cout << games << std::endl;*/
    vectorGames.push_back("pepito");
    vectorGames.push_back("foo");
    vectorGames.push_back("bar"); //todo recibir esto del server
    return vectorGames;
}