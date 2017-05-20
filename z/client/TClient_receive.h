
#ifndef CLIENT_TCLIENT_RECEIVE_H
#define CLIENT_TCLIENT_RECEIVE_H


#include "Thread.h"
#include "Socket.h"
#include "Game_map.h"

class TClient_receive: public tThread {
private:
    tSocket &socket;
    Game_map &game_map;

public:
    TClient_receive(tSocket &s, Game_map &game_map);
    ~TClient_receive();
    void run();

};


#endif //CLIENT_TCLIENT_RECEIVE_H
