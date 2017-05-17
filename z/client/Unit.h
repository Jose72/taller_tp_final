//
// Created by matias on 15/05/17.
//

#ifndef CLIENT_UNIT_H
#define CLIENT_UNIT_H


#include <SDL_video.h>
#include <vector>
#include "Animation.h"

class Unit {
protected:
    SDL_Surface *screen;
    int posx;
    int posy;
    int current_frame;
    std::vector<Animation *> animation;
public:

    Unit();
    ~Unit();
    void animate();
    void set_pos(int x,int y);
    int get_posx();
    int get_posy();





};


#endif //CLIENT_UNIT_H
