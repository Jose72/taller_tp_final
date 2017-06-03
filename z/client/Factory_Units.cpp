#include "Factory_Units.h"

Factory_Units::Factory_Units(SpritesPool &pool):pool(pool) {}

Unit* Factory_Units::createUnit(FlagsUnitType unit,int unit_code, int posx, int posy) {
    std::vector<Animation*> animation;
    std::vector<Animation*> animation2;
    std::vector<Animation*> animation3;
    std::vector<Animation*> animation4;
    std::vector<Animation*> animation5;
    switch (unit){
        case BLUE_GRUNT:
            animation  = this->pool.get_animations(BLUE_GRUNT);
            animation2 = this->pool.get_animations(FIRE_BLUE_GRUNT);
            animation3 = this->pool.get_animations(DIE_BLUE_GRUNT);
            animation4 = this->pool.get_animations(BEER_BLUE);
            animation5 = this->pool.get_animations(CELEBRATE_BLUE);
            return new Unit(animation,animation2,animation3,animation4,animation5,unit_code,posx,posy);
        case GREEN_GRUNT:
            animation  = this->pool.get_animations(GREEN_GRUNT);
            animation2 = this->pool.get_animations(FIRE_GREEN_GRUNT);
            animation3 = this->pool.get_animations(DIE_GREEN_GRUNT);
            animation4 = this->pool.get_animations(BEER_GREEN);
            animation5 = this->pool.get_animations(CELEBRATE_GREEN);
            return new Unit(animation,animation2,animation3,animation4,animation5,unit_code,posx,posy);
        case RED_GRUNT:
            animation  = this->pool.get_animations(RED_GRUNT);
            animation2 = this->pool.get_animations(FIRE_RED_GRUNT);
            animation3 = this->pool.get_animations(DIE_RED_GRUNT);
            animation4 = this->pool.get_animations(BEER_RED);
            animation5 = this->pool.get_animations(CELEBRATE_RED);
            return new Unit(animation,animation2,animation3,animation4,animation5,unit_code,posx,posy);

        case YELLOW_GRUNT:
            animation  = this->pool.get_animations(YELLOW_GRUNT);
            animation2 = this->pool.get_animations(FIRE_YELLOW_GRUNT);
            animation3 = this->pool.get_animations(DIE_YELLOW_GRUNT);
            animation4 = this->pool.get_animations(BEER_YELLOW);
            animation5 = this->pool.get_animations(CELEBRATE_YELLOW);
            return new Unit(animation,animation2,animation3,animation4,animation5,unit_code,posx,posy);

        case COLORLESS_FLAG:
        animation = this->pool.get_animations(COLORLESS_FLAG);
            return new Unit(animation,animation,animation,animation,animation,unit_code,posx,posy);
        case FORT_SPRITE:
            animation = this->pool.get_animations(FORT_SPRITE);
            return new Unit(animation,animation,animation,animation,animation,unit_code,posx,posy);


    }

}
