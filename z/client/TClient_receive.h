
#ifndef CLIENT_TCLIENT_RECEIVE_H
#define CLIENT_TCLIENT_RECEIVE_H



#include "Game_map.h"
#include "Unit.h"
#include "Factory_Units.h"
#include "../common/Thread.h"
#include "../common/Socket.h"

class TClient_receive: public tThread {
private:
    tSocket &socket;
    Game_map &game_map;
    std::vector<Unit*> &units;
    Factory_Units  &factory;

public:
    TClient_receive(tSocket &s, Game_map &game_map,std::vector<Unit*> &u, Factory_Units &f);
    ~TClient_receive();
    void run();
    void stop();

};


#endif //CLIENT_TCLIENT_RECEIVE_H
