//
// Created by mbataglia on 22/05/17.
//

#ifndef Z_PLAYERINTERFACE_H
#define Z_PLAYERINTERFACE_H


#include <SDL_video.h>
#include <SDL_image.h>
#include "Animation.h"
#include "SelectionHandler.h"

class PlayerInterface {
private:
    SDL_Surface * screen;
    SelectionHandler* selectionHandler;
    int gameWidth;
    int gameHeight;
    int width;
    Animation *background;
public:
    PlayerInterface(SDL_Surface* screen,
                    SelectionHandler* selectionHandler,
                        int gameWidth,
                        int gameHeight,
                        int width);

    void show();

    virtual ~PlayerInterface();

};


#endif //Z_PLAYERINTERFACE_H
