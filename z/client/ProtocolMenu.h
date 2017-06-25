//
// Created by mbataglia on 06/06/17.
//

#ifndef Z_PROTOCOLMENU_H
#define Z_PROTOCOLMENU_H


#include "../common/Socket.h"
#include "InfoGameSelection.h"


#define CREATE_GAME 0
#define JOIN_GAME 1
#define DEATHMATCH 0
#define TEAM_GAME 1
#define RESPONSE_PROTOCOL_MENU_OK 0
#define RESPONSE_PROTOCOL_MENU_FULL_TEAM -1
#define NO_TEAM_PARAM -1

struct mapData{
    std::string mapName;
    int cantEquipos;
    int dimensions;
};

class ProtocolMenu {
public:
    ProtocolMenu(tSocket &socket);
    int initCreateGame();
    virtual ~ProtocolMenu();
    int createGame(int numPlayers, int typeGame, int numTeams);
    int initJoinGame();
    void infoJoinGame();
    int joinGame(int idCreator, int i);
    std::vector<InfoGameSelection*> infoGames;
    int receive_id_client();
    std::vector<mapData>receiveMapsInfo();
    void sendMapName(std::string mapName);

private:
    tSocket &socket;



    void cleanInfoGames();



};


#endif //Z_PROTOCOLMENU_H