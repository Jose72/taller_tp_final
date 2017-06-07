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
    BLUE_FLAG,
    GREEN_FLAG,
    RED_FLAG,
    YELLOW_FLAG,
    MISILE_LAUNCHER_BLUE,
    MISILE_LAUNCHER_GREEN,
    MISILE_LAUNCHER_RED,
    MISILE_LAUNCHER_YELLOW,
    FORT_SPRITE
};

class SpritesPool {
private:
    SDL_Surface *screen;
    std::map<FlagsUnitType ,std::vector<Animation*>> pool;

public:
    SpritesPool(SDL_Surface *screen);
    std::vector<Animation*> &get_animations(FlagsUnitType flag);
    void load_sprites(std::string path,
                      FlagsUnitType blue,
                      FlagsUnitType green,
                      FlagsUnitType red,
                      FlagsUnitType yellow);

    void load_sprites_with_null(std::string path,
                                FlagsUnitType null,
                                FlagsUnitType blue,
                                FlagsUnitType green,
                                FlagsUnitType red,
                                FlagsUnitType yellow);

    void load_sprites_with_dim(std:: string path,
                               FlagsUnitType blue,
                               FlagsUnitType green,
                               FlagsUnitType red,
                               FlagsUnitType yellow,
                               int dimensions);


};


#endif //CLIENT_SPRITESPOOL_H
