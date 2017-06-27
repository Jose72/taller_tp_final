//
// Created by mbataglia on 23/05/17.
//

#ifndef Z_DRAWER_H
#define Z_DRAWER_H


#include "Animation.h"
#include "TTF_Writter.h"
#include "ClickableButton.h"
#include <string>

class Drawer {
private:
    TTF_Writter writter;
public:
    void drawLine(SDL_Surface *screen, int y);

    void drawBackground(int gameWidth, int gameHeight,
                        int width, Animation *background);

    void
    drawText(SDL_Surface *screen, std::string msj,
             int x, int y);


    int drawImage(SDL_Surface *surface, const char *image_path,
                  Sint16 x_pos, Sint16 y_pos);

    void drawButton(SDL_Surface *screen,
                    ClickableButton *pButton);

    void drawGiantText(SDL_Surface *screen, std::string msj,
                       int x, int y);
};


#endif //Z_DRAWER_H
