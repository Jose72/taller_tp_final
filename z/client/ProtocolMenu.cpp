//
// Created by mbataglia on 06/06/17.
//

#include <vector>
#include <string>
#include <iostream>
#include "ProtocolMenu.h"
#include "InfoGameSelection.h"
#define SIZE_INT 4




ProtocolMenu::ProtocolMenu(tSocket &socket) : socket(socket) {}

int ProtocolMenu::receive_id_client() {
    int id_c;
    socket.receive((char*)&id_c,SIZE_INT);
    int id_c_SC =ntohl(id_c);
    return id_c_SC;
}

int ProtocolMenu::initCreateGame() {
    int CO_to_send = htonl(CREATE_GAME);
    socket.send((char*) &CO_to_send,SIZE_INT);
    int response;
    socket.receive((char*)&response,SIZE_INT);
    return ntohl(response);
}

int ProtocolMenu::createGame(int numPlayers,int typeGame,int numTeams) {
    int numPlayers_to_send = htonl(numPlayers);
    socket.send((char*) &numPlayers_to_send,SIZE_INT);
    int typeGame_to_send = htonl(typeGame);
    socket.send((char*) &typeGame_to_send,SIZE_INT);
    int numTeams_to_send = htonl(numTeams);
    socket.send((char*) &numTeams_to_send,SIZE_INT);
    int response;
    socket.receive((char*)&response,SIZE_INT);
    return ntohl(response);
}

int ProtocolMenu::initJoinGame() {
    int CO_to_send = htonl(JOIN_GAME);
    socket.send((char*) &CO_to_send,SIZE_INT);
    int response;
    socket.receive((char*)&response,SIZE_INT);
    return ntohl(response);
}

int ProtocolMenu::joinGame(int idCreator, int team) {
    int idCreator_to_send = htonl(idCreator);
    socket.send((char*) &idCreator_to_send,SIZE_INT);
    //todo
    //ENVIAR EQUIPO AL QUE SE UNE, SI ESTA OK ESPERA 0
    //SI EL EQUIPO ESTA LLENO ESPERA -1 Y VUELVE A LA PANTALLA DE SELECCION DE EQUIPOS
    //PARA VOLVER A MANDAR ID DEL CREADOR Y DEL EQUIPO
    //PARA DEATHMATCH SE MANDA EQUIPO -1
    //VER MAINWINDOW UNIRSE CUALQUIER COSA

    int idTeam_to_send = htonl(team);
    socket.send((char*) &idTeam_to_send,SIZE_INT);
    int response;
    socket.receive((char*)&response,SIZE_INT);
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

    socket.receive((char*)&numGamesNet,SIZE_INT);
    numGames = ntohl(numGamesNet);

    for (int i= 0; i < numGames; i++){
        socket.receive((char*)&idCreatorNet,SIZE_INT);
        idCreator = ntohl(idCreatorNet);

        socket.receive((char*)&maxPlayersNet,SIZE_INT);
        maxPlayers = ntohl(maxPlayersNet);

        socket.receive((char*)&joinedPlayersNet,SIZE_INT);
        joinedPlayers = ntohl(joinedPlayersNet);

        socket.receive((char*)&typeGameNet,SIZE_INT);
        typeGame = ntohl(typeGameNet);

        socket.receive((char*)&numTeamsNet,SIZE_INT);
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


std::vector<mapData> ProtocolMenu::receiveMapsInfo() {
    std::vector<mapData> vecMapsData;
    int cantMaps;
    socket.receive((char*) &cantMaps,SIZE_INT);
    int cantMapsSC = ntohl(cantMaps);
    for (int i = 0; i <cantMapsSC ; ++i) {
        mapData data;
        int nameSize;
        socket.receive((char*) &nameSize,SIZE_INT);
        int nameSizeSC = ntohl(nameSize);
        char name [nameSizeSC];
        socket.receive(name,nameSizeSC);
        int dim;
        socket.receive((char*) &dim,SIZE_INT);
        int dimSC = ntohl(dim);
        int equipos;
        socket.receive((char*) &equipos,SIZE_INT);
        int equiposSC = ntohl(equipos);
        std::string nameMap(name);
        data.mapName = nameMap;
        data.dimensions = dimSC;
        data.cantEquipos = equiposSC;
        vecMapsData.push_back(data);
    }
    return vecMapsData;
}

void ProtocolMenu::sendMapName(std::string mapName) {
    int name_size = mapName.size();
    int nameSizeCS = htonl(name_size);
    socket.send((char*)&nameSizeCS, SIZE_INT);
    socket.send(&mapName[0u], mapName.size());

}


ProtocolMenu::~ProtocolMenu() {
    cleanInfoGames();
}
