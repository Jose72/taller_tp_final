//
// Created by mbataglia on 06/06/17.
//

#ifndef Z_PROTOCOLMENU_H
#define Z_PROTOCOLMENU_H


#include "../common/Socket.h"

class ProtocolMenu {
public:
    ProtocolMenu(tSocket &socket);
    std::vector<std::string> fetchGames();
private:
    tSocket &socket;


};


#endif //Z_PROTOCOLMENU_H