//
// Created by mbataglia on 22/05/17.
//

#ifndef Z_PLAYERINTERFACE_H
#define Z_PLAYERINTERFACE_H


#include <SDL_video.h>
#include <SDL_image.h>
#include "Animation.h"
#include "SelectionHandler.h"
#include "TTF_Writter.h"
#include "Drawer.h"
#include "ClickableButton.h"

class PlayerInterface {
private:
    SDL_Surface * screen;
    int gameWidth;
    int gameHeight;
    int width;
    Animation *background;
    Drawer drawer;
    std::vector<ClickableButton*> buttons;
public:
    PlayerInterface(SDL_Surface* screen,
                        int gameWidth,
                        int gameHeight,
                        int width);

    void show(SelectionHandler &selectionHandler);

    virtual ~PlayerInterface();

    int getCol(int division, int offset);

    int getCol(int division, int offset, int sizeElement);

    bool checkClickedButtons(int x, int y);
};


#endif //Z_PLAYERINTERFACE_H
