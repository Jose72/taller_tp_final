#include "Factory_Units.h"

Factory_Units::Factory_Units(SpritesPool &pool):pool(pool) {}

Unit* Factory_Units::createUnit(FlagsUnitType unit,int unit_code, int posx, int posy) {

    switch (unit){
        case BLUE_GRUNT:
            return new Unit(this->pool.get_animations(BLUE_GRUNT),
                            this->pool.get_animations(FIRE_BLUE_GRUNT),
                            this->pool.get_animations(DIE_BLUE_GRUNT),
                            this->pool.get_animations(BEER_BLUE),
                            this->pool.get_animations(CELEBRATE_BLUE),
                            unit_code,posx,posy,DRINKING,BLUE_GRUNT);
        case GREEN_GRUNT:
            return new Unit (this->pool.get_animations(GREEN_GRUNT),
                             this->pool.get_animations(FIRE_GREEN_GRUNT),
                             this->pool.get_animations(DIE_GREEN_GRUNT),
                             this->pool.get_animations(BEER_GREEN),
                             this->pool.get_animations(CELEBRATE_GREEN),
                             unit_code,posx,posy, DRINKING,GREEN_GRUNT);
        case RED_GRUNT:
            return new Unit(this->pool.get_animations(RED_GRUNT),
                            this->pool.get_animations(FIRE_RED_GRUNT),
                            this->pool.get_animations(DIE_RED_GRUNT),
                            this->pool.get_animations(BEER_RED),
                            this->pool.get_animations(CELEBRATE_RED),
                            unit_code,posx,posy, DRINKING, RED_GRUNT);

        case YELLOW_GRUNT:
            return new Unit(this->pool.get_animations(YELLOW_GRUNT),
                            this->pool.get_animations(FIRE_YELLOW_GRUNT),
                            this->pool.get_animations(DIE_YELLOW_GRUNT),
                            this->pool.get_animations(BEER_YELLOW),
                            this->pool.get_animations(CELEBRATE_YELLOW),
                            unit_code,posx,posy, DRINKING, YELLOW_GRUNT);

        case BLUE_TOUGHT:
            return new Unit(this->pool.get_animations(BLUE_GRUNT),
                            this->pool.get_animations(FIRE_BLUE_GRUNT),
                            this->pool.get_animations(DIE_BLUE_GRUNT),
                            this->pool.get_animations(BEER_BLUE),
                            this->pool.get_animations(CELEBRATE_BLUE),
                            unit_code,posx,posy,DRINKING,BLUE_TOUGHT);
        case GREEN_TOUGHT:
            return new Unit (this->pool.get_animations(GREEN_GRUNT),
                             this->pool.get_animations(FIRE_GREEN_GRUNT),
                             this->pool.get_animations(DIE_GREEN_GRUNT),
                             this->pool.get_animations(BEER_GREEN),
                             this->pool.get_animations(CELEBRATE_GREEN),
                             unit_code,posx,posy, DRINKING,GREEN_TOUGHT);
        case RED_TOUGHT:
            return new Unit(this->pool.get_animations(RED_GRUNT),
                            this->pool.get_animations(FIRE_RED_GRUNT),
                            this->pool.get_animations(DIE_RED_GRUNT),
                            this->pool.get_animations(BEER_RED),
                            this->pool.get_animations(CELEBRATE_RED),
                            unit_code,posx,posy, DRINKING, RED_TOUGHT);

        case YELLOW_TOUGHT:
            return new Unit(this->pool.get_animations(YELLOW_GRUNT),
                            this->pool.get_animations(FIRE_YELLOW_GRUNT),
                            this->pool.get_animations(DIE_YELLOW_GRUNT),
                            this->pool.get_animations(BEER_YELLOW),
                            this->pool.get_animations(CELEBRATE_YELLOW),
                            unit_code,posx,posy, DRINKING, YELLOW_TOUGHT);

        case BLUE_PYRO:
            return new Unit(this->pool.get_animations(BLUE_GRUNT),
                            this->pool.get_animations(FIRE_BLUE_GRUNT),
                            this->pool.get_animations(DIE_BLUE_GRUNT),
                            this->pool.get_animations(BEER_BLUE),
                            this->pool.get_animations(CELEBRATE_BLUE),
                            unit_code,posx,posy,DRINKING,BLUE_PYRO);
        case GREEN_PYRO:
            return new Unit (this->pool.get_animations(GREEN_GRUNT),
                             this->pool.get_animations(FIRE_GREEN_GRUNT),
                             this->pool.get_animations(DIE_GREEN_GRUNT),
                             this->pool.get_animations(BEER_GREEN),
                             this->pool.get_animations(CELEBRATE_GREEN),
                             unit_code,posx,posy, DRINKING,GREEN_PYRO);
        case RED_PYRO:
            return new Unit(this->pool.get_animations(RED_GRUNT),
                            this->pool.get_animations(FIRE_RED_GRUNT),
                            this->pool.get_animations(DIE_RED_GRUNT),
                            this->pool.get_animations(BEER_RED),
                            this->pool.get_animations(CELEBRATE_RED),
                            unit_code,posx,posy, DRINKING, RED_PYRO);

        case YELLOW_PYRO:
            return new Unit(this->pool.get_animations(YELLOW_GRUNT),
                            this->pool.get_animations(FIRE_YELLOW_GRUNT),
                            this->pool.get_animations(DIE_YELLOW_GRUNT),
                            this->pool.get_animations(BEER_YELLOW),
                            this->pool.get_animations(CELEBRATE_YELLOW),
                            unit_code,posx,posy, DRINKING, YELLOW_PYRO);

        case BLUE_PSYCHO:
            return new Unit(this->pool.get_animations(BLUE_GRUNT),
                            this->pool.get_animations(FIRE_BLUE_GRUNT),
                            this->pool.get_animations(DIE_BLUE_GRUNT),
                            this->pool.get_animations(BEER_BLUE),
                            this->pool.get_animations(CELEBRATE_BLUE),
                            unit_code,posx,posy,DRINKING,BLUE_PSYCHO);
        case GREEN_PSYCHO:
            return new Unit (this->pool.get_animations(GREEN_GRUNT),
                             this->pool.get_animations(FIRE_GREEN_GRUNT),
                             this->pool.get_animations(DIE_GREEN_GRUNT),
                             this->pool.get_animations(BEER_GREEN),
                             this->pool.get_animations(CELEBRATE_GREEN),
                             unit_code,posx,posy, DRINKING,GREEN_PSYCHO);
        case RED_PSYCHO:
            return new Unit(this->pool.get_animations(RED_GRUNT),
                            this->pool.get_animations(FIRE_RED_GRUNT),
                            this->pool.get_animations(DIE_RED_GRUNT),
                            this->pool.get_animations(BEER_RED),
                            this->pool.get_animations(CELEBRATE_RED),
                            unit_code,posx,posy, DRINKING, RED_PSYCHO);

        case YELLOW_PSYCHO:
            return new Unit(this->pool.get_animations(YELLOW_GRUNT),
                            this->pool.get_animations(FIRE_YELLOW_GRUNT),
                            this->pool.get_animations(DIE_YELLOW_GRUNT),
                            this->pool.get_animations(BEER_YELLOW),
                            this->pool.get_animations(CELEBRATE_YELLOW),
                            unit_code,posx,posy, DRINKING, YELLOW_PSYCHO);

        case BLUE_SNIPER:
            return new Unit(this->pool.get_animations(BLUE_GRUNT),
                            this->pool.get_animations(FIRE_BLUE_GRUNT),
                            this->pool.get_animations(DIE_BLUE_GRUNT),
                            this->pool.get_animations(BEER_BLUE),
                            this->pool.get_animations(CELEBRATE_BLUE),
                            unit_code,posx,posy,DRINKING,BLUE_SNIPER);
        case GREEN_SNIPER:
            return new Unit (this->pool.get_animations(GREEN_GRUNT),
                             this->pool.get_animations(FIRE_GREEN_GRUNT),
                             this->pool.get_animations(DIE_GREEN_GRUNT),
                             this->pool.get_animations(BEER_GREEN),
                             this->pool.get_animations(CELEBRATE_GREEN),
                             unit_code,posx,posy, DRINKING,GREEN_SNIPER);
        case RED_SNIPER:
            return new Unit(this->pool.get_animations(RED_GRUNT),
                            this->pool.get_animations(FIRE_RED_GRUNT),
                            this->pool.get_animations(DIE_RED_GRUNT),
                            this->pool.get_animations(BEER_RED),
                            this->pool.get_animations(CELEBRATE_RED),
                            unit_code,posx,posy, DRINKING, RED_SNIPER);

        case YELLOW_SNIPER:
            return new Unit(this->pool.get_animations(YELLOW_GRUNT),
                            this->pool.get_animations(FIRE_YELLOW_GRUNT),
                            this->pool.get_animations(DIE_YELLOW_GRUNT),
                            this->pool.get_animations(BEER_YELLOW),
                            this->pool.get_animations(CELEBRATE_YELLOW),
                            unit_code,posx,posy, DRINKING, YELLOW_SNIPER);

        case BLUE_LASER:
            return new Unit(this->pool.get_animations(BLUE_GRUNT),
                            this->pool.get_animations(FIRE_LASER_BLUE),
                            this->pool.get_animations(DIE_BLUE_GRUNT),
                            this->pool.get_animations(BEER_BLUE),
                            this->pool.get_animations(CELEBRATE_BLUE),
                            unit_code,posx,posy, DRINKING,BLUE_LASER);
        case GREEN_LASER:
            return new Unit (this->pool.get_animations(GREEN_GRUNT),
                             this->pool.get_animations(FIRE_LASER_GREEN),
                             this->pool.get_animations(DIE_GREEN_GRUNT),
                             this->pool.get_animations(BEER_GREEN),
                             this->pool.get_animations(CELEBRATE_GREEN),
                             unit_code,posx,posy, DRINKING,GREEN_LASER);
        case RED_LASER:
            return new Unit(this->pool.get_animations(RED_GRUNT),
                            this->pool.get_animations(FIRE_LASER_RED),
                            this->pool.get_animations(DIE_RED_GRUNT),
                            this->pool.get_animations(BEER_RED),
                            this->pool.get_animations(CELEBRATE_RED),
                            unit_code,posx,posy, DRINKING,GREEN_LASER);

        case YELLOW_LASER:
            return new Unit(this->pool.get_animations(YELLOW_GRUNT),
                            this->pool.get_animations(FIRE_LASER_YELLOW),
                            this->pool.get_animations(DIE_YELLOW_GRUNT),
                            this->pool.get_animations(BEER_YELLOW),
                            this->pool.get_animations(CELEBRATE_YELLOW),
                            unit_code,posx,posy,DRINKING,GREEN_LASER);

        case MISILE_LAUNCHER_BLUE:
            return new Unit(this->pool.get_animations(MISILE_LAUNCHER_BLUE),
                            this->pool.get_animations(MISILE_LAUNCHER_BLUE),
                            this->pool.get_animations(MISILE_LAUNCHER_BLUE),
                            this->pool.get_animations(MISILE_LAUNCHER_BLUE),
                            this->pool.get_animations(MISILE_LAUNCHER_BLUE),
                            unit_code,posx,posy,ROLLING,MISILE_LAUNCHER_BLUE);

        case MISILE_LAUNCHER_GREEN:
            return  new Unit(this->pool.get_animations(MISILE_LAUNCHER_GREEN),
                             this->pool.get_animations(MISILE_LAUNCHER_GREEN),
                             this->pool.get_animations(MISILE_LAUNCHER_GREEN),
                             this->pool.get_animations(MISILE_LAUNCHER_GREEN),
                             this->pool.get_animations(MISILE_LAUNCHER_GREEN),
                             unit_code,posx,posy,ROLLING,MISILE_LAUNCHER_GREEN);

        case MISILE_LAUNCHER_RED:
            return new Unit(this->pool.get_animations(MISILE_LAUNCHER_RED),
                            this->pool.get_animations(MISILE_LAUNCHER_RED),
                            this->pool.get_animations(MISILE_LAUNCHER_RED),
                            this->pool.get_animations(MISILE_LAUNCHER_RED),
                            this->pool.get_animations(MISILE_LAUNCHER_RED),
                            unit_code,posx,posy,ROLLING, MISILE_LAUNCHER_RED);

        case MISILE_LAUNCHER_YELLOW:
            return  new Unit(this->pool.get_animations(MISILE_LAUNCHER_YELLOW),
                             this->pool.get_animations(MISILE_LAUNCHER_YELLOW),
                             this->pool.get_animations(MISILE_LAUNCHER_YELLOW),
                             this->pool.get_animations(MISILE_LAUNCHER_YELLOW),
                             this->pool.get_animations(MISILE_LAUNCHER_YELLOW),
                             unit_code,posx,posy,ROLLING, MISILE_LAUNCHER_YELLOW);

        case COLORLESS_FLAG:
            return new Unit(this->pool.get_animations(COLORLESS_FLAG),
                            this->pool.get_animations(BLUE_FLAG),
                            this->pool.get_animations(RED_FLAG),
                            this->pool.get_animations(GREEN_FLAG),
                            this->pool.get_animations(YELLOW_FLAG),
                            unit_code,posx,posy,COLORLESS, COLORLESS_FLAG);
        case FORT_SPRITE:
            return new Unit(this->pool.get_animations(FORT_SPRITE),
                            this->pool.get_animations(FORT_SPRITE),
                            this->pool.get_animations(FORT_SPRITE),
                            this->pool.get_animations(FORT_SPRITE),
                            this->pool.get_animations(FORT_SPRITE),
                            unit_code,posx,posy,DRINKING,FORT_SPRITE);
        case LASER_BULLET:
            return new Unit(this->pool.get_animations(LASER_BULLET),
                            this->pool.get_animations(LASER_BULLET),
                            this->pool.get_animations(BULLET_DEAD_JOSE_WAY),
                            this->pool.get_animations(LASER_BULLET),
                            this->pool.get_animations(LASER_BULLET),
                            unit_code,posx,posy,BULLETTIME,LASER_BULLET);
    }

}
