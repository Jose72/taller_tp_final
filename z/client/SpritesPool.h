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
    BLUE_PSYCHO,
    GREEN_PSYCHO,
    RED_PSYCHO,
    YELLOW_PSYCHO,
    BLUE_TOUGHT,
    GREEN_TOUGHT,
    RED_TOUGHT,
    YELLOW_TOUGHT,
    BLUE_PYRO,
    GREEN_PYRO,
    RED_PYRO,
    YELLOW_PYRO,
    BLUE_SNIPER,
    GREEN_SNIPER,
    RED_SNIPER,
    YELLOW_SNIPER,
    BLUE_LASER,
    GREEN_LASER,
    RED_LASER,
    YELLOW_LASER,
    FIRE_BLUE_GRUNT,
    FIRE_GREEN_GRUNT,
    FIRE_RED_GRUNT,
    FIRE_YELLOW_GRUNT,
    FIRE_LASER_BLUE,
    FIRE_LASER_GREEN,
    FIRE_LASER_RED,
    FIRE_LASER_YELLOW,
    FIRE_PSYCHO_BLUE,
    FIRE_PSYCHO_GREEN,
    FIRE_PSYCHO_RED,
    FIRE_PSYCHO_YELLOW,
    FIRE_PYRO_BLUE,
    FIRE_PYRO_GREEN,
    FIRE_PYRO_RED,
    FIRE_PYRO_YELLOW,
    FIRE_SNIPER_BLUE,
    FIRE_SNIPER_GREEN,
    FIRE_SNIPER_RED,
    FIRE_SNIPER_YELLOW,
    FIRE_TOUGHT_BLUE,
    FIRE_TOUGHT_GREEN,
    FIRE_TOUGHT_RED,
    FIRE_TOUGHT_YELLOW,
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
    LIGHT_TANK_BLUE,
    LIGHT_TANK_GREEN,
    LIGHT_TANK_RED,
    LIGHT_TANK_YELLOW,
    MEDIUM_TANK_BLUE,
    MEDIUM_TANK_GREEN,
    MEDIUM_TANK_RED,
    MEDIUM_TANK_YELLOW,
    HEAVY_TANK_BLUE,
    HEAVY_TANK_GREEN,
    HEAVY_TANK_RED,
    HEAVY_TANK_YELLOW,
    JEEP_BLUE,
    JEEP_GREEN,
    JEEP_RED,
    JEEP_YELLOW,
    FORT_ALIVE,
    FORT_DEAD,
    FACTORY_ROBOTS_ALIVE,
    FACTORY_ROBOTS_DEAD,
    FACTORY_VEHICLES_ALIVE,
    FACTORY_VEHICLES_DEAD,
    LASER_BULLET,
    PYRO_BULLET,
    TOUGHT_BULLET,
    HCP_BULLET,
    BULLET_DEAD
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

    void load_sprite(std::string path,
                     FlagsUnitType blue,
                     std::string keyword,
                     int x, int y);


};


#endif //CLIENT_SPRITESPOOL_H
