#ifndef CLIENT_EVENTHANDLER_H
#define CLIENT_EVENTHANDLER_H
#include "../common/Thread.h"
#include "PlayerInterface.h"
#include "Game_map.h"
#include "Factory_Units.h"
#include "WinnerProtected.h"
#include "SoundManager.h"

class EventHandler: public tThread {
private:
    SDL_Surface *screen;
    PlayerInterface &playerInterface;
    Units_Protected &units;
    tSocket &socket;
    Game_map &gameMap;
    bool &running;
    Factory_Units &factory;
    int &id_client;
    TechLevelProtected &techLevel;
    WinnerProtected &winner;
    SoundManager &soundManager;


public:
    EventHandler(SDL_Surface *screen,
                 PlayerInterface &p,
                 Units_Protected &u,
                 tSocket &s,
                 Game_map &m, bool &b,
                 Factory_Units &f,
                 int &id_client, TechLevelProtected &tech,WinnerProtected &winner,
                SoundManager &soundManager);
    ~EventHandler();
    void run();
    void stop();

private:
    void checkDead();



};


#endif //CLIENT_EVENTHANDLER_H

