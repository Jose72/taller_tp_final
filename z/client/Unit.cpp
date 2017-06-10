#include <iostream>
#include "Unit.h"

#define FRAME_LIMIT_BULLET 1
#define FRAME_LIMIT_2 2
#define FRAME_LIMIT_DEAD 9
#define FRAME_LIMIT_DRINK 9
#define FRAME_LIMIT_CELEBRATE 3
#define FRAME_LIMIT_FLAG 3
#define FRAME_LIMIT_MOVE_GRUNT 3
#define FRAME_LIMIT_ATTACK_GRUNT 4

Unit::Unit(std::vector<Animation*> &a0,
           std::vector<Animation*> &a1,
           std::vector<Animation*> &a2,
           std::vector<Animation*> &a3,
           std::vector<Animation*> &a4,
           int cu,
           int posx,
           int posy,
           State state,
           FlagsUnitType unitType):
        animation(a0),animation2(a1),animation3(a2),animation4(a3),animation5(a4),posx(posx),posy(posy) {

    this->cod_unit = cu;
    this->state = state;
    this->unitType = unitType;
}


Unit::~Unit() {
    for (int i = 0; i <animation.size() ; ++i) {
        delete (this->animation[i]);
    }
}
void Unit::animate(SDL_Rect &cameraRect) {
    switch(state){
        case BULLETTIME:
            animate_moving(cameraRect,animation,FRAME_LIMIT_BULLET);
            break;

        case MOVING1:
            animate_moving(cameraRect,animation,FRAME_LIMIT_MOVE_GRUNT);
            break;

        case ATTACKING1:
            if(unitType != LASER_BULLET){
                animate_attacking(cameraRect,animation2,FRAME_LIMIT_ATTACK_GRUNT);
            }
            break;

        case DEAD1:
            animate_static(cameraRect,animation3,FRAME_LIMIT_DEAD);
            if((current_frame == FRAME_LIMIT_DEAD)){
                this->set_state(DEAD2);
            }
            break;

        case DEAD2:
            break;

        case DRINKING:
            animate_static(cameraRect,animation4,FRAME_LIMIT_DRINK);
            break;

        case CELEBRATE:
            animate_static(cameraRect,animation5,FRAME_LIMIT_CELEBRATE);
            break;

        case COLORLESS:
            animate_static(cameraRect,animation,FRAME_LIMIT_FLAG);
            break;

        case BLUE:
            animate_static(cameraRect,animation2,FRAME_LIMIT_FLAG);
            break;

        case GREEN:
            animate_static(cameraRect,animation3, FRAME_LIMIT_FLAG);
            break;

        case RED:
            animate_static(cameraRect,animation4,FRAME_LIMIT_FLAG);
            break;

        case YELLOW:
            animate_static(cameraRect,animation5, FRAME_LIMIT_FLAG);
            break;

        case ROLLING:
            animate_moving(cameraRect,animation,FRAME_LIMIT_2);
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
    std::cout<< posX_attack << "\n";
    std::cout<< posY_attack << "\n";
    std::cout<< posx << "\n";
    std::cout<< posy << "\n";
    if((posx < posX_attack) && (posy == posY_attack)){
        this->attack_direction = ZERO_A;
    } else if((posx < posX_attack) && (posy > posY_attack)){
        this->attack_direction = ONE_A;
    } else if((posx == posX_attack) && (posy > posY_attack)){
        this->attack_direction = TWO_A;
    } else if((posx > posX_attack) && (posy > posY_attack)){
        this->attack_direction = THREE_A;
    } else if((posx > posX_attack) && (posy == posY_attack)){
        this->attack_direction = FOUR_A;
    } else if((posx > posX_attack) && (posy < posY_attack)){
        this->attack_direction = FIVE_A;
    } else if((posx == posX_attack) && (posy < posY_attack)){
        this->attack_direction = SIX_A;
    } else if((posx < posX_attack) && (posy < posY_attack)){
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

void Unit::animate_static(SDL_Rect &cameraRect, std::vector<Animation *> &a, int max_frame) {
    if(current_frame < max_frame){
        current_frame ++;
    } else{
        current_frame = 0;
    }
    a[current_frame]->animate(posx,posy,cameraRect);
}

void Unit::animate_moving(SDL_Rect &cameraRect, std::vector<Animation *> &a, int max_frame) {
    int framePos = max_frame;
    if(current_frame< max_frame){
        ++current_frame;
    } else{
        current_frame = 0;
    }
    switch (direction){
        case ZERO:
            if((posx == posxO) && (posy == posyO)){
                animation[0]->animate(posx,posy,cameraRect);
            }else {
                animation[current_frame]->animate(posx,posy,cameraRect);
            }
            break;

        case ONE:
            if((posx == posxO) && (posy == posyO)){
                animation[framePos]->animate(posx,posy,cameraRect);
            }else {
                animation[current_frame + framePos]->animate(posx,posy,cameraRect);
            }
            break;

        case TWO:
            if((posx == posxO) && (posy == posyO)){
                animation[(2*framePos)]->animate(posx,posy,cameraRect);
            }else {
                animation[current_frame + (2*framePos) ]->animate(posx,posy,cameraRect);
            }
            break;

        case THREE:
            if((posx == posxO) && (posy == posyO)){
                animation[(3*framePos)]->animate(posx,posy,cameraRect);
            }else {
                animation[current_frame + (3*framePos)]->animate(posx,posy,cameraRect);
            }
            break;

        case FOUR:
            if((posx == posxO) && (posy == posyO)) {
                animation[(4*framePos)]->animate(posx,posy,cameraRect);
            }else {
                animation[current_frame + (4*framePos)]->animate(posx,posy,cameraRect);
            }
            break;

        case FIVE:
            if((posx == posxO) && (posy == posyO)) {
                animation[(5*framePos)]->animate(posx,posy,cameraRect);
            }else {
                animation[current_frame + (5*framePos)]->animate(posx,posy,cameraRect);
            }
            break;

        case SIX:
            if((posx == posxO) && (posy == posyO)) {
                animation[(6*framePos)]->animate(posx,posy,cameraRect);
            }else {
                animation[current_frame + (6*framePos)]->animate(posx,posy,cameraRect);
            }
            break;

        case SEVEN:
            if((posx == posxO) && (posy == posyO)) {
                animation[(7*framePos)]->animate(posx,posy,cameraRect);
            }else{
                animation[current_frame + (7*framePos)]->animate(posx,posy,cameraRect);
            }
            break;
        default:
            animation[0]->animate(posx,posy,cameraRect);
            break;
    }
}

void Unit::animate_attacking(SDL_Rect &cameraRect, std::vector<Animation *> &a, int max_frame) {
    int framePos = max_frame;
    if(current_frame< max_frame){
        ++current_frame;
    } else{
        current_frame = 0;
    }
    switch (attack_direction){
        case ZERO_A:
            animation2[current_frame]->animate(posx,posy,cameraRect);
            break;

        case ONE_A:
            animation2[current_frame + framePos]->animate(posx,posy,cameraRect);
            break;

        case TWO_A:
            animation2[current_frame + (2*framePos)]->animate(posx,posy,cameraRect);
            break;

        case THREE_A:
            animation2[current_frame + (3*framePos)]->animate(posx,posy,cameraRect);
            break;

        case FOUR_A:
            animation2[current_frame + (4*framePos)]->animate(posx,posy,cameraRect);
            break;

        case FIVE_A:
            animation2[current_frame + (5*framePos)]->animate(posx,posy,cameraRect);
            break;

        case SIX_A:
            animation2[current_frame + (6*framePos)]->animate(posx,posy,cameraRect);
            break;

        case SEVEN_A:
            animation2[current_frame + (7*framePos)]->animate(posx,posy,cameraRect);
            break;

        default:
            animation2[0]->animate(posx,posy,cameraRect);
            break;
    }
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

FlagsUnitType Unit::get_type() {
    return  this->unitType;
}

