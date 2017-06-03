#include "Unit.h"

#define FRAME_LIMIT_S1 3
#define FRAME_LIMIT_S2 4
#define FRAME_LIMIT_S3 9
#define FRAME_LIMIT_S4 9
#define FRAME_LIMIT_S5 3

Unit::Unit(std::vector<Animation*> &a0,
           std::vector<Animation*> &a1,
           std::vector<Animation*> &a2,
           std::vector<Animation*> &a3,
           std::vector<Animation*> &a4,
           int cu,
           int posx,
           int posy):
        animation(a0),animation2(a1),animation3(a2),animation4(a3),animation5(a4),posx(posx),posy(posy) {

    this->current_frame_move = 0;
    this->current_frame_attack = 0;
    this->current_frame_die = 0;
    this->current_frame_drink = 0;
    this->current_frame_celebrate = 0;
    this->cod_unit = cu;
    state = DRINKING;
}

Unit::~Unit() {
    for (int i = 0; i <animation.size() ; ++i) {
        delete (this->animation[i]);
    }
}
void Unit::animate(SDL_Rect &cameraRect) {
    switch(state){
        case MOVING:
            animate_move(cameraRect);
            break;

        case ATTACKING:
            animate_attack(cameraRect);
            break;

        case DEAD:
            animate_die(cameraRect);
            break;

        case DRINKING:
            animate_drink(cameraRect);
            break;

        case CELEBRATE:
            animate_celebrate(cameraRect);
            break;
    }
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

void Unit::set_attack(int posX, int posY) {
    this->posX_attack = posX;
    this->posY_attack = posY;
    if((posx > posX_attack) && (posy == posY_attack)){
        this->attack_direction = ZERO_A;
    } else if((posx > posX_attack) && (posy < posY_attack)){
        this->attack_direction = ONE_A;
    } else if((posx == posX_attack) && (posy < posY_attack)){
        this->attack_direction = TWO_A;
    } else if((posx < posX_attack) && (posy < posY_attack)){
        this->attack_direction = THREE_A;
    } else if((posx < posX_attack) && (posy == posY_attack)){
        this->attack_direction = FOUR_A;
    } else if((posx < posX_attack) && (posy > posY_attack)){
        this->attack_direction = FIVE_A;
    } else if((posx == posX_attack) && (posy > posY_attack)){
        this->attack_direction = SIX_A;
    } else if((posx > posX_attack) && (posy > posY_attack)){
        this->attack_direction = SEVEN_A;
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
int Unit::get_unit_code() {
    return  this->cod_unit;
}

void Unit::animate_move(SDL_Rect &cameraRect) {
    if(current_frame_move< FRAME_LIMIT_S1){
        ++current_frame_move;
    } else{
        current_frame_move = 0;
    }
    switch (direction){
        case ZERO:
            if((posx == posxO) && (posy == posyO)){
                animation[0]->animate(posx,posy,cameraRect);
            }else {
                animation[current_frame_move]->animate(posx,posy,cameraRect);
            }
            break;

        case ONE:
            if((posx == posxO) && (posy == posyO)){
                animation[4]->animate(posx,posy,cameraRect);
            }else {
                animation[current_frame_move + 4]->animate(posx,posy,cameraRect);
            }
            break;

        case TWO:
            if((posx == posxO) && (posy == posyO)){
                animation[8]->animate(posx,posy,cameraRect);
            }else {
                animation[current_frame_move + 8]->animate(posx,posy,cameraRect);
            }
            break;

        case THREE:
            if((posx == posxO) && (posy == posyO)){
                animation[12]->animate(posx,posy,cameraRect);
            }else {
                animation[current_frame_move + 12]->animate(posx,posy,cameraRect);
            }
            break;

        case FOUR:
            if((posx == posxO) && (posy == posyO)) {
                animation[16]->animate(posx,posy,cameraRect);
            }else {
                animation[current_frame_move + 16]->animate(posx,posy,cameraRect);
            }
            break;

        case FIVE:
            if((posx == posxO) && (posy == posyO)) {
                animation[20]->animate(posx,posy,cameraRect);
            }else {
                animation[current_frame_move + 20]->animate(posx,posy,cameraRect);
            }
            break;

        case SIX:
            if((posx == posxO) && (posy == posyO)) {
                animation[24]->animate(posx,posy,cameraRect);
            }else {
                animation[current_frame_move + 24]->animate(posx,posy,cameraRect);
            }
            break;

        case SEVEN:
            if((posx == posxO) && (posy == posyO)) {
                animation[28]->animate(posx,posy,cameraRect);
            }else{
                animation[current_frame_move + 28]->animate(posx,posy,cameraRect);
            }
            break;
        default:
            animation[0]->animate(posx,posy,cameraRect);
            break;
    }

}

void Unit::animate_attack(SDL_Rect &cameraRect) {
    if(current_frame_attack< FRAME_LIMIT_S2){
        ++current_frame_attack;
    } else{
        current_frame_attack = 0;
    }
    switch (attack_direction){
        case ZERO_A:
            animation2[current_frame_attack]->animate(posx,posy,cameraRect);
            break;

        case ONE_A:
            animation2[current_frame_attack + 5]->animate(posx,posy,cameraRect);
            break;

        case TWO_A:
            animation2[current_frame_attack + 9]->animate(posx,posy,cameraRect);
            break;

        case THREE_A:
            animation2[current_frame_attack + 13]->animate(posx,posy,cameraRect);
            break;

        case FOUR_A:
            animation2[current_frame_attack + 17]->animate(posx,posy,cameraRect);
            break;

        case FIVE_A:
            animation2[current_frame_attack + 21]->animate(posx,posy,cameraRect);
            break;

        case SIX_A:
            animation2[current_frame_attack + 25]->animate(posx,posy,cameraRect);
            break;

        case SEVEN_A:
            animation2[current_frame_attack + 29]->animate(posx,posy,cameraRect);
            break;

        default:
            animation2[0]->animate(posx,posy,cameraRect);
            break;
    }
}

void Unit::animate_die(SDL_Rect &cameraRect) {
    if(current_frame_die < FRAME_LIMIT_S3){
        current_frame_die ++;
    } else{
        current_frame_die = FRAME_LIMIT_S3;
    }
    animation3[current_frame_die]->animate(posx,posy,cameraRect);
}

void Unit::animate_drink(SDL_Rect &cameraRect) {
    if(current_frame_drink < FRAME_LIMIT_S4){
        current_frame_drink ++;
    } else{
        current_frame_drink = 0;
    }
    animation4[current_frame_drink]->animate(posx,posy,cameraRect);
}

void Unit::animate_celebrate(SDL_Rect &cameraRect) {
    if(current_frame_celebrate < FRAME_LIMIT_S5){
        current_frame_celebrate ++;
    } else{
        current_frame_celebrate = 0;
    }
    animation5[current_frame_celebrate]->animate(posx,posy,cameraRect);
}

void Unit::set_state(State s) {
    this->state = s;
}

void Unit::set_health(int health) {
    this->health = health;
}

State Unit::get_state() {
    return this->state;
}

int Unit::get_heatlh() {
    return this->health;
}

