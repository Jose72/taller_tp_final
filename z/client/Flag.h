//
// Created by matias on 15/05/17.
//

#ifndef CLIENT_FLAG_H
#define CLIENT_FLAG_H


#include <vector>
#include "Animation.h"
#include "Unit.h"

class Flag: public Unit{
public:
    Flag(SDL_Surface *screen,int posx, int posy);

};


#endif //CLIENT_FLAG_H
