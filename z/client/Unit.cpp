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
