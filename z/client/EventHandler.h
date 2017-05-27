#ifndef CLIENT_EVENTHANDLER_H
#define CLIENT_EVENTHANDLER_H


#include "Camera.h"
#include "../common/Thread.h"
#include "PlayerInterface.h"

class EventHandler: public tThread {
private:
    SDL_Surface *screen;
    Camera &gameCamera;
    PlayerInterface &playerInterface;
    Units_Protected &units;
    tSocket &socket;
    Game_map &gameMap;
    bool &running;

public:
    EventHandler(SDL_Surface *screen,Camera &c, PlayerInterface &p, Units_Protected &u, tSocket &s, Game_map &m, bool &b);
    ~EventHandler();
    void run();
    void stop();



};


#endif //CLIENT_EVENTHANDLER_H

