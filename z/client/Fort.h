#ifndef CLIENT_FORT_H
#define CLIENT_FORT_H

#include <SDL_video.h>
#include <vector>
#include "Animation.h"
#include "Unit.h"

class Fort: public Unit {
public:
    Fort(SDL_Surface *screen,int x, int y);
};


#endif //CLIENT_FORT_H
