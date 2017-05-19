#include "Unit.h"

#define FRAME_LIMIT 3
Unit::Unit(std::vector<Animation*> animation, int posx, int posy):
        animation(animation),posx(posx),posy(posy) {
    this->current_frame = 0;
}

Unit::~Unit() {
    for (int i = 0; i <animation.size() ; ++i) {
        delete (this->animation[i]);
    }
}
void Unit::animate() {
    if(current_frame< FRAME_LIMIT){
        ++current_frame;
    } else{
        current_frame = 0;
    }
    //animation[current_frame]->animate(this->cameraPosX,this->cameraPosY);

    switch (direction){
        case ZERO:
            if((posx == posxO) && (posy == posyO)){
                animation[0]->animate(this->cameraPosX,this->cameraPosY);
            }else {
                animation[current_frame]->animate(this->cameraPosX,this->cameraPosY);
            }
            break;

        case ONE:
            if((posx == posxO) && (posy == posyO)){
                animation[4]->animate(this->cameraPosX,this->cameraPosY);
            }else {
                animation[current_frame + 4]->animate(this->cameraPosX, this->cameraPosY);
            }
            break;

        case TWO:
            if((posx == posxO) && (posy == posyO)){
                animation[8]->animate(this->cameraPosX, this->cameraPosY);
            }else {
                animation[current_frame + 8]->animate(this->cameraPosX, this->cameraPosY);
            }
            break;

        case THREE:
            if((posx == posxO) && (posy == posyO)){
                animation[12]->animate(this->cameraPosX,this->cameraPosY);
            }else {
                animation[current_frame + 12]->animate(this->cameraPosX,this->cameraPosY);
            }
            break;

        case FOUR:
            if((posx == posxO) && (posy == posyO)) {
                animation[16]->animate(this->cameraPosX, this->cameraPosY);
            }else {
                animation[current_frame + 16]->animate(this->cameraPosX, this->cameraPosY);
            }
            break;

        case FIVE:
            if((posx == posxO) && (posy == posyO)) {
                animation[20]->animate(this->cameraPosX, this->cameraPosY);
            }else {
                animation[current_frame + 20]->animate(this->cameraPosX,this->cameraPosY);
            }
            break;

        case SIX:
            if((posx == posxO) && (posy == posyO)) {
                animation[24]->animate(this->cameraPosX,this->cameraPosY);
            }else {
                animation[current_frame + 24]->animate(this->cameraPosX,this->cameraPosY);
            }
            break;

        case SEVEN:
            if((posx == posxO) && (posy == posyO)) {
                animation[28]->animate(this->cameraPosX,this->cameraPosY);
            }else{
                animation[current_frame + 28]->animate(this->cameraPosX,this->cameraPosY);
            }
            break;
        default:
            animation[0]->animate(this->cameraPosX,this->cameraPosY);
            break;
    }
    //animation[current_frame]->animate(this->posx,this->posy);


}
void Unit::set_pos(int x, int y) {
    this->posxO = this->posx;
    this->posyO = this->posy;
    this->posx = x;
    this->posy = y;
    if((posx > posxO) && (posy == posyO)){
        this->direction = ZERO;
    } else if((posx > posxO) && (posy < posyO)){
        this->direction = ONE;
    } else if((posx == posxO) && (posy < posyO)){
        this->direction = TWO;
    } else if((posx < posxO) && (posy < posyO)){
        this->direction = THREE;
    } else if((posx < posxO) && (posy == posyO)){
        this->direction = FOUR;
    } else if((posx < posxO) && (posy > posyO)){
        this->direction = FIVE;
    } else if((posx == posxO) && (posy > posyO)){
        this->direction = SIX;
    } else if((posx > posxO) && (posy > posyO)){
        this->direction = SEVEN;
    }

}

int Unit::get_posx() {
    return this->posx;
}

int Unit::get_posy() {
    return  this->posy;
}

void Unit::set_pos_camera(int x, int y) {
    this->cameraPosX = x;
    this->cameraPosY = y;
}

int Unit::get_cameraPosX() {
    return this->cameraPosX;
}

int Unit::get_cameraPosY() {
    return this->cameraPosY;
}
