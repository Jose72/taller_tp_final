//
// Created by mbataglia on 22/05/17.
//

#include <iostream>
#include "PlayerInterface.h"
#include "Animation.h"



PlayerInterface::PlayerInterface(SDL_Surface* screen,
                                 SelectionHandler* selectionHandler,
                                 int gameWidth,
                                 int gameHeight,
                                 int width){
    this->screen = screen;
    this->selectionHandler = selectionHandler;
    this->gameWidth = gameWidth;
    this->gameHeight = gameHeight;
    this->width = width;
    this->background = new Animation(this->screen,"client/sprites/tiles/5.bmp",32,32);
}

int DrawImage( SDL_Surface *surface, char *image_path, int x_pos, int y_pos )
{
    SDL_Surface *image = IMG_Load ( image_path );
    if ( !image )
    {
        printf ( "IMG_Load: %s\n", IMG_GetError () );
        return 1;
    }

    // Draws the image on the screen:
    SDL_Rect rcDest = { x_pos, y_pos, 0, 0 };
    SDL_BlitSurface ( image, NULL, surface, &rcDest );

    // something like SDL_UpdateRect(surface, x_pos, y_pos, image->w, image->h); is missing here

    SDL_FreeSurface ( image );
    return 0;
}

void PlayerInterface::show() {
    bool locked = SDL_MUSTLOCK(screen);
    if(locked)
        SDL_LockSurface(screen);

    Uint32 *pixels = (Uint32 *)screen->pixels;
    int pixelNum = screen->w * screen->h;


    for (int j = gameWidth; j < gameWidth + width; j = j +32) {
        for (int k = 0; k < gameHeight; k = k+32) {
            background->animate(j, k);
        }
    }

    for(int i = gameWidth; i < pixelNum;) {
        pixels[i] = SDL_MapRGB(screen->format, 255, 255, 255);
        pixels[i+1] = SDL_MapRGB(screen->format, 255, 255, 255);
        pixels[i+2] = SDL_MapRGB(screen->format, 255, 255, 255);
        pixels[i+3] = SDL_MapRGB(screen->format, 255, 255, 255);
        pixels[i+4] = SDL_MapRGB(screen->format, 255, 255, 255);
        i += gameWidth + width;
    }

    if(selectionHandler->unit_select()){
       // std::cout << selectionHandler->getUnit()->get_cameraPosX() << std::endl;
    } else {
        //std::cout << "nada seleccionado" << std::endl;
    }

    DrawImage(screen,"client/sprites/portraits/grunt_blue/SHEADBI2_0002.png", gameWidth + 100, 100);//hacer funcion calcule posicion

    if(locked)
        SDL_UnlockSurface(screen);
}

PlayerInterface::~PlayerInterface() {
    delete(background);
}

