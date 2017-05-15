#include "flag.h"

Flag::Flag(SDL_Surface *screen,int posx, int posy) {
    this->screen = screen;
    this->posx = posx;
    this->posy = posy;
    this->current_frame = 0;
    Animation *flag0 = new Animation(this->screen,
                                     "/home/matias/Escritorio/Client/sprites/flags/0.bmp",
                                     16,16,0);
    this->animation.push_back(flag0);
    Animation*flag1 = new Animation(this->screen,
                                    "/home/matias/Escritorio/Client/sprites/flags/1.bmp",
                                    16,16,0);
    this->animation.push_back(flag1);
    Animation *flag2 = new Animation(this->screen,
                                     "/home/matias/Escritorio/Client/sprites/flags/2.bmp",
                                     16,16,0);
    this->animation.push_back(flag2);
    Animation*flag3 = new Animation(this->screen,
                                    "/home/matias/Escritorio/Client/sprites/flags/3.bmp",
                                    16,16,0);
    this->animation.push_back(flag3);
}

Flag::~Flag() {
    for (int i = 0; i <animation.size() ; ++i) {
        delete(this->animation[i]);

    }

}

void Flag::animate_flag() {
    if(current_frame<3){
        ++current_frame;
    } else{
        current_frame = 0;
    }
    animation[current_frame]->animate(this->posx,this->posy);
}
