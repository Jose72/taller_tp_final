//
// Created by matias on 15/05/17.
//

#ifndef CLIENT_UNIT_H
#define CLIENT_UNIT_H


#include <SDL_video.h>
#include <vector>
#include "Animation.h"
#include "SpritesPool.h"

class Unit {
protected:
    int posx;
    int posy;
    int current_frame;
    std::vector<Animation *> animation;
public:

    Unit( std::vector<Animation *> animation, int posx, int posy);
    Unit();
    ~Unit();
    void animate();
    void set_pos(int x,int y);
    int get_posx();
    int get_posy();





};


#endif //CLIENT_UNIT_H
