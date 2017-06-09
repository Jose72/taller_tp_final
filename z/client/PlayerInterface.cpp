//
// Created by mbataglia on 22/05/17.
//

#include <iostream>
#include <SDL_ttf.h>
#include "PlayerInterface.h"
#include "Animation.h"
#include "ClickableButtonGrunt.h"
#include "ClickableButtonLaser.h"


PlayerInterface::PlayerInterface(SDL_Surface* screen,
                                 int gameWidth,
                                 int gameHeight,
                                 int width){
    this->screen = screen;
    this->gameWidth = gameWidth;
    this->gameHeight = gameHeight;
    this->width = width;
    this->background = new Animation(this->screen,"client/sprites/tiles/5.bmp",32,32);
    buttons.push_back(new ClickableButtonGrunt(getCol(2,1,100),300,50,100,"Grunt"));
    buttons.push_back(new ClickableButtonLaser(getCol(2,1,100),400,50,100,"Laser"));
}

int PlayerInterface::getCol(int division,int offset,int sizeElement){
    return gameWidth + (width/division) * offset - sizeElement;
}

bool PlayerInterface::checkClickedButtons(int x, int y){
    bool result = false;
    for(int i = 0; i != buttons.size(); i++) {
        result = result || buttons[i]->checkBounds(x,y);
    }
    return result;
}

void PlayerInterface::show(SelectionHandler& selectionHandler) {
    bool locked = SDL_MUSTLOCK(screen);
    if(locked)
        SDL_LockSurface(screen);

    drawer.drawBackground(gameWidth,gameHeight,width,background);
    drawer.drawLine(screen,gameWidth);
    drawer.drawImage(screen,"client/sprites/portraits/grunt_blue/SHEADBI2_0002.png", getCol(2,1,32), 80);//hacer funcion calcule posicion
    drawer.drawText(screen,"Z",getCol(2,1,0),0);
    if(selectionHandler.unit_select()){
        drawer.drawText(screen,std::to_string(selectionHandler.getUnit()->get_posx()),getCol(2,1,0),150);
        drawer.drawText(screen,std::to_string(selectionHandler.getUnit()->get_posy()),getCol(2,1,0),170);
    } else {
        drawer.drawText(screen,"Nada seleccionado",getCol(2,1,0),150);;
    }

    for(int i = 0; i != buttons.size(); i++) {
        drawer.drawButton(screen,buttons[i]);
    }


    if(locked)
        SDL_UnlockSurface(screen);
}

PlayerInterface::~PlayerInterface() {
    for(int i = 0; i != buttons.size(); i++) {
        delete(buttons[i]);
    }
    delete(background);
}

