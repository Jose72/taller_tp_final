//
// Created by mbataglia on 06/06/17.
//

#include <vector>
#include <string>
#include <iostream>
#include "ProtocolMenu.h"
#include "InfoGameSelection.h"






ProtocolMenu::ProtocolMenu(tSocket &socket) : socket(socket) {}

int ProtocolMenu::receive_id_client() {
    int id_c;
    socket.receive((char*)&id_c,4);
    int id_c_SC =ntohl(id_c);
    return id_c_SC;
}

int ProtocolMenu::initCreateGame() {
    int CO_to_send = htonl(CREATE_GAME);
    socket.send((char*) &CO_to_send,sizeof(int));
    int response;
    socket.receive((char*)&response,4);
    return ntohl(response);
}

int ProtocolMenu::createGame(int numPlayers,int typeGame,int numTeams) {
    int numPlayers_to_send = htonl(numPlayers);
    socket.send((char*) &numPlayers_to_send,sizeof(int));
    int typeGame_to_send = htonl(typeGame);
    socket.send((char*) &typeGame_to_send,sizeof(int));
    int numTeams_to_send = htonl(numTeams);
    socket.send((char*) &numTeams_to_send,sizeof(int));
    int response;
    socket.receive((char*)&response,4);
    return ntohl(response);
}

int ProtocolMenu::initJoinGame() {
    int CO_to_send = htonl(JOIN_GAME);
    socket.send((char*) &CO_to_send,sizeof(int));
    int response;
    socket.receive((char*)&response,4);
    return ntohl(response);
}

int ProtocolMenu::joinGame(int idCreator) {
    int idCreator_to_send = htonl(idCreator);
    socket.send((char*) &idCreator_to_send,sizeof(int));
    int response;
    socket.receive((char*)&response,4);
    return ntohl(response);
}



void ProtocolMenu::infoJoinGame(){
    cleanInfoGames();
    int numGamesNet;
    int numGames;
    int idCreatorNet;
    int idCreator;
    int maxPlayersNet;
    int maxPlayers;
    int joinedPlayersNet;
    int joinedPlayers;
    int typeGameNet;
    int typeGame;
    int numTeamsNet;
    int numTeams;

    socket.receive((char*)&numGamesNet,4);
    numGames = ntohl(numGamesNet);

    for (int i= 0; i < numGames; i++){
        socket.receive((char*)&idCreatorNet,4);
        idCreator = ntohl(idCreatorNet);

        socket.receive((char*)&maxPlayersNet,4);
        maxPlayers = ntohl(maxPlayersNet);

        socket.receive((char*)&joinedPlayersNet,4);
        joinedPlayers = ntohl(joinedPlayersNet);

        socket.receive((char*)&typeGameNet,4);
        typeGame = ntohl(typeGameNet);

        socket.receive((char*)&numTeamsNet,4);
        numTeams = ntohl(numTeamsNet);

        infoGames.push_back(new InfoGameSelection(idCreator,maxPlayers,joinedPlayers,typeGame,numTeams));
    }

}

void ProtocolMenu::cleanInfoGames(){
    for (int i = 0; i < infoGames.size(); i++){
        delete infoGames[i];
    }
    infoGames.clear();
}

ProtocolMenu::~ProtocolMenu() {
    cleanInfoGames();
}
