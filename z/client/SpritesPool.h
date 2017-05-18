#ifndef CLIENT_SPRITESPOOL_H
#define CLIENT_SPRITESPOOL_H

#include <map>
#include <vector>
#include "Animation.h"

enum FlagsUnitType{
    BLUE_GRUNT = 11,
    YELLOW_GRUNT = 12,
    COLORLESS_FLAG = 90,
    FORT = 100
};

class SpritesPool {
private:
    SDL_Surface *screen;
    std::map<FlagsUnitType ,std::vector<Animation*>> pool;

public:
    SpritesPool(SDL_Surface *screen);
    std::vector<Animation*> get_animations(FlagsUnitType flag);

};


#endif //CLIENT_SPRITESPOOL_H
