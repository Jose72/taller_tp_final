//
// Created by matias on 15/05/17.
//

#ifndef CLIENT_FLAG_H
#define CLIENT_FLAG_H


#include <vector>
#include "Animation.h"

class Flag {
private:
    SDL_Surface *screen;
    int posx;
    int posy;
    int current_frame;

    std::vector<Animation *> animation;
public:
    Flag(SDL_Surface *screen,int posx, int posy);
    ~Flag();
    void animate_flag();

};


#endif //CLIENT_FLAG_H
