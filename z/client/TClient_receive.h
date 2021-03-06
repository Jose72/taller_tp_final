
#ifndef CLIENT_TCLIENT_RECEIVE_H
#define CLIENT_TCLIENT_RECEIVE_H


#include "../common/Thread.h"
#include "../common/Socket.h"
#include "Game_map.h"
#include "Unit.h"
#include "Factory_Units.h"
#include "Units_Protected.h"
#include "TechLevelProtected.h"
#include "WinnerProtected.h"
#include "SoundManager.h"

class TClient_receive: public tThread {
private:
    tSocket &socket;
    Game_map &game_map;
    Units_Protected &units;
    Factory_Units  &factory;
    bool &done;
    bool &running;
    int &id_client;
    int &dimensions;
    int &posXI;
    int &posYI;
    TechLevelProtected &techLevel;
    WinnerProtected &winner;
    SoundManager &soundManager;


public:
    TClient_receive(tSocket &s,
                    Game_map &game_map,
                    Units_Protected &u,
                    Factory_Units &f,
                    bool &done,
                    bool &r,
                    int &id_c,
                    int &dimensions,
                    int &posXI,
                    int &posYI,
                    TechLevelProtected &tech,
                    WinnerProtected &winner,
                    SoundManager &soundManager);
    ~TClient_receive();
    void run();
    void stop();
};


#endif //CLIENT_TCLIENT_RECEIVE_H
