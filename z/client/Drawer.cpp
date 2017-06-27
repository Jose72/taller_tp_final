//
// Created by mbataglia on 23/05/17.
//

#include <SDL_video.h>
#include "Drawer.h"
#include "Animation.h"
#include <string>
#include <SDL_image.h>

void Drawer::drawLine(SDL_Surface* screen,int y) {
    Uint32 *pixels = (Uint32 *)screen->pixels;
    int pixelNum = screen->w * screen->h;
    for(int i = y; i < pixelNum;) {
        pixels[i] = SDL_MapRGB(screen->format, 255, 255, 255);
        pixels[i+1] = SDL_MapRGB(screen->format, 255, 255, 255);
        pixels[i+2] = SDL_MapRGB(screen->format, 255, 255, 255);
        pixels[i+3] = SDL_MapRGB(screen->format, 255, 255, 255);
        pixels[i+4] = SDL_MapRGB(screen->format, 255, 255, 255);
        i += screen->w;
    }
}

void Drawer::drawBackground(int gameWidth,int gameHeight,
                            int width, Animation* background) {
    for (int j = gameWidth; j < gameWidth + width; j = j +32) {
        for (int k = 0; k < gameHeight; k = k+32) {
            background->animate_static(j, k);
        }
    }
}


void Drawer::drawText(SDL_Surface *screen, std::string msj,
                      int x, int y){
    writter.drawText(screen,msj,x-(msj.size()*3),y);
}

void Drawer::drawGiantText(SDL_Surface *screen, std::string msj,
                           int x, int y){
    writter.drawGiantText(screen,msj,x-(msj.size()*3),y);
}

int Drawer::drawImage(SDL_Surface *surface, const char *image_path,
                      Sint16 x_pos, Sint16 y_pos) {
    SDL_Surface *image = IMG_Load ( image_path );
    if ( !image ) {
        printf ( "IMG_Load: %s, path: %s\n", IMG_GetError (),image_path );
        return 1;
    }

    // Draws the image on the screen:
    SDL_Rect rcDest = { x_pos, y_pos, 0, 0 };
    SDL_BlitSurface ( image, NULL, surface, &rcDest );

    SDL_FreeSurface ( image );
    return 0;
}

void Drawer::drawButton(SDL_Surface *screen, ClickableButton *pButton){
    drawImage(screen,"client/sprites/buttons/fus_top.png",
              pButton->getX(),pButton->getY());
    drawText(screen,pButton->getText(),pButton->getX()+30,pButton->getY());
}