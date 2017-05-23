#ifndef CLIENT_SPRITESPOOL_H
#define CLIENT_SPRITESPOOL_H

#include <map>
#include <vector>
#include "Animation.h"

enum FlagsUnitType{
    BLUE_GRUNT = 11,
    GREEN_GRUNT = 12,
    RED_GRUNT = 13,
    YELLOW_GRUNT = 14,
    FIRE_BLUE_GRUNT = 21,
    FIRE_GREEN_GRUNT = 22,
    FIRE_RED_GRUNT = 23,
    FIRE_YELLOW_GRUNT = 24,
    FIRE_LASER_BLUE = 31,
    FIRE_LASER_GREEN = 32,
    FIRE_LASER_RED = 33,
    FIRE_LASER_YELLOW = 34,
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
    void load_fire_grunt();
    void load_sprites(char* path,FlagsUnitType blue, FlagsUnitType green, FlagsUnitType red, FlagsUnitType yellow);

};


#endif //CLIENT_SPRITESPOOL_H
