#include "Flag.h"

Flag::Flag(SDL_Surface *screen, int posx, int posy) {
    this->screen = screen;
    this->posx = posx;
    this->posy = posy;
    this->current_frame = 0;
    Animation *flag0 = new Animation(this->screen,
                                     "/home/matias/Escritorio/Client/sprites/flags/0.bmp",
                                     16,16);
    this->animation.push_back(flag0);
    Animation*flag1 = new Animation(this->screen,
                                    "/home/matias/Escritorio/Client/sprites/flags/1.bmp",
                                    16,16);
    this->animation.push_back(flag1);
    Animation *flag2 = new Animation(this->screen,
                                     "/home/matias/Escritorio/Client/sprites/flags/2.bmp",
                                     16,16);
    this->animation.push_back(flag2);
    Animation*flag3 = new Animation(this->screen,
                                    "/home/matias/Escritorio/Client/sprites/flags/3.bmp",
                                    16,16);
    this->animation.push_back(flag3);
}



