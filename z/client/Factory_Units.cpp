#include "Factory_Units.h"

Factory_Units::Factory_Units(SpritesPool &pool):pool(pool) {}

Unit* Factory_Units::createUnit(FlagsUnitType unit,int unit_code, int posx, int posy) {

    switch (unit){
        case BLUE_GRUNT:
            return new Unit(this->pool.get_animations(BLUE_GRUNT),
                            this->pool.get_animations(FIRE_BLUE_GRUNT),
                            this->pool.get_animations(DIE_BLUE_GRUNT),
                            this->pool.get_animations(BEER_BLUE),
                            this->pool.get_animations(CELEBRATE_BLUE),unit_code,posx,posy);
        case GREEN_GRUNT:
            return new Unit (this->pool.get_animations(GREEN_GRUNT),
                             this->pool.get_animations(FIRE_GREEN_GRUNT),
                             this->pool.get_animations(DIE_GREEN_GRUNT),
                             this->pool.get_animations(BEER_GREEN),
                             this->pool.get_animations(CELEBRATE_GREEN),
                             unit_code,posx,posy);
        case RED_GRUNT:
            return new Unit(this->pool.get_animations(RED_GRUNT),
                            this->pool.get_animations(FIRE_RED_GRUNT),
                            this->pool.get_animations(DIE_RED_GRUNT),
                            this->pool.get_animations(BEER_RED),
                            this->pool.get_animations(CELEBRATE_RED),
                            unit_code,posx,posy);

        case YELLOW_GRUNT:
            return new Unit(this->pool.get_animations(YELLOW_GRUNT),
                            this->pool.get_animations(FIRE_YELLOW_GRUNT),
                            this->pool.get_animations(DIE_YELLOW_GRUNT),
                            this->pool.get_animations(BEER_YELLOW),
                            this->pool.get_animations(CELEBRATE_YELLOW),
                            unit_code,posx,posy);

        case MISILE_LAUNCHER_BLUE:
            return new Unit(this->pool.get_animations(MISILE_LAUNCHER_BLUE),
                            this->pool.get_animations(MISILE_LAUNCHER_BLUE),
                            this->pool.get_animations(MISILE_LAUNCHER_BLUE),
                            this->pool.get_animations(MISILE_LAUNCHER_BLUE),
                            this->pool.get_animations(MISILE_LAUNCHER_BLUE),
                            unit_code,posx,posy,ROLLING);

        case MISILE_LAUNCHER_GREEN:
            return  new Unit(this->pool.get_animations(MISILE_LAUNCHER_GREEN),
                             this->pool.get_animations(MISILE_LAUNCHER_GREEN),
                             this->pool.get_animations(MISILE_LAUNCHER_GREEN),
                             this->pool.get_animations(MISILE_LAUNCHER_GREEN),
                             this->pool.get_animations(MISILE_LAUNCHER_GREEN),
                             unit_code,posx,posy,ROLLING);

        case MISILE_LAUNCHER_RED:
            return new Unit(this->pool.get_animations(MISILE_LAUNCHER_RED),
                            this->pool.get_animations(MISILE_LAUNCHER_RED),
                            this->pool.get_animations(MISILE_LAUNCHER_RED),
                            this->pool.get_animations(MISILE_LAUNCHER_RED),
                            this->pool.get_animations(MISILE_LAUNCHER_RED),
                            unit_code,posx,posy,ROLLING);

        case MISILE_LAUNCHER_YELLOW:
            return  new Unit(this->pool.get_animations(MISILE_LAUNCHER_YELLOW),
                             this->pool.get_animations(MISILE_LAUNCHER_YELLOW),
                             this->pool.get_animations(MISILE_LAUNCHER_YELLOW),
                             this->pool.get_animations(MISILE_LAUNCHER_YELLOW),
                             this->pool.get_animations(MISILE_LAUNCHER_YELLOW),
                             unit_code,posx,posy,ROLLING);

        case COLORLESS_FLAG:
            return new Unit(this->pool.get_animations(COLORLESS_FLAG),
                            this->pool.get_animations(BLUE_FLAG),
                            this->pool.get_animations(RED_FLAG),
                            this->pool.get_animations(GREEN_FLAG),
                            this->pool.get_animations(YELLOW_FLAG),
                            unit_code,posx,posy,COLORLESS);
        case FORT_SPRITE:
            return new Unit(this->pool.get_animations(FORT_SPRITE),
                            this->pool.get_animations(FORT_SPRITE),
                            this->pool.get_animations(FORT_SPRITE),
                            this->pool.get_animations(FORT_SPRITE),
                            this->pool.get_animations(FORT_SPRITE),
                            unit_code,posx,posy);
    }

}
