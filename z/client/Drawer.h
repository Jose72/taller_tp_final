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

    void drawBackground(int gameWidth, int gameHeight, int width, Animation *background);

    void
    drawText(SDL_Surface *screen, std::string msj, int x, int y);


    int drawImage(SDL_Surface *surface, char *image_path, int x_pos, int y_pos);

    void drawButton(SDL_Surface *screen,ClickableButton *&pButton);
};


#endif //Z_DRAWER_H
