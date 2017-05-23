#include "Factory_Units.h"

Factory_Units::Factory_Units(SpritesPool &pool):pool(pool) {}

Unit* Factory_Units::createUnit(FlagsUnitType unit, int posx, int posy) {
    std::vector<Animation*> animation;
    switch (unit){
        case BLUE_GRUNT:
        animation = this->pool.get_animations(BLUE_GRUNT);
            return new Unit(animation,posx,posy);
        case GREEN_GRUNT:
            animation = this->pool.get_animations(GREEN_GRUNT);
            return new Unit(animation,posx,posy);
        case RED_GRUNT:
            animation = this->pool.get_animations(RED_GRUNT);
            return new Unit(animation,posx,posy);
        case YELLOW_GRUNT:
            animation = this->pool.get_animations(YELLOW_GRUNT);
            return new Unit(animation,posx,posy);
        case COLORLESS_FLAG:
        animation = this->pool.get_animations(COLORLESS_FLAG);
            return new Unit(animation,posx,posy);
        case FORT:
            animation = this->pool.get_animations(FORT);
            return  new Unit(animation,posx,posy);

    }

}
