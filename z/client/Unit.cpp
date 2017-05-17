#include "Unit.h"

Unit::Unit() {}
Unit::~Unit() {
    for (int i = 0; i <animation.size() ; ++i) {
        delete (this->animation[i]);
    }
}
void Unit::animate() {
    if(current_frame<(animation.size()-1)){
        ++current_frame;
    } else{
        current_frame = 0;
    }
    animation[current_frame]->animate(this->posx,this->posy);

}
void Unit::set_pos(int x, int y) {
    this->posx = x;
    this->posy = y;
}

int Unit::get_posx() {
    return this->posx;
}

int Unit::get_posy() {
    return  this->posy;
}
