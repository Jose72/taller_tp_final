#ifndef CLIENT_SPRITESPOOL_H
#define CLIENT_SPRITESPOOL_H

#include <map>
#include <vector>
#include "Animation.h"

enum FlagsUnitType{
    BLUE_GRUNT,
    GREEN_GRUNT,
    RED_GRUNT,
    YELLOW_GRUNT,
    FIRE_BLUE_GRUNT,
    FIRE_GREEN_GRUNT,
    FIRE_RED_GRUNT,
    FIRE_YELLOW_GRUNT,
    FIRE_LASER_BLUE,
    FIRE_LASER_GREEN,
    FIRE_LASER_RED,
    FIRE_LASER_YELLOW,
    DIE_BLUE_GRUNT,
    DIE_GREEN_GRUNT,
    DIE_RED_GRUNT,
    DIE_YELLOW_GRUNT,
    BEER_BLUE,
    BEER_GREEN,
    BEER_RED,
    BEER_YELLOW,
    CELEBRATE_BLUE,
    CELEBRATE_GREEN,
    CELEBRATE_RED,
    CELEBRATE_YELLOW,
    COLORLESS_FLAG,
    FORT_SPRITE
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
