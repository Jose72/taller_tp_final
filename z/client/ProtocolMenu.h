//
// Created by mbataglia on 06/06/17.
//

#ifndef Z_PROTOCOLMENU_H
#define Z_PROTOCOLMENU_H


#include "../common/Socket.h"
#include "InfoGameSelection.h"

#define RESPONSE_PROTOCOL_MENU_OK 0
class ProtocolMenu {
public:
    ProtocolMenu(tSocket &socket);
    int initCreateGame();
    virtual ~ProtocolMenu();
    int createGame(int numPlayers, int typeGame, int numTeams);
    int initJoinGame();
    void infoJoinGame();
    int joinGame(int idCreator);
    std::vector<InfoGameSelection*> infoGames;

private:
    tSocket &socket;



    void cleanInfoGames();




};


#endif //Z_PROTOCOLMENU_H