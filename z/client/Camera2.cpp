#include "Camera2.h"

#define BETWEEN(value, min, max) (((value) < (max)) && ((value) > (min)))

Camera2::Camera2(int posX, int posY, int W, int H, int lW, int lH, Factory_Units &f):factory(f) {
    this->cameraRect.x = posX;
    this->cameraRect.y = posY;
    this->cameraRect.w = W;
    this->cameraRect.h = H;
    this->posCameraRectX = posX;
    this->posCameraRectY = posY;
    this->cameraW = W;
    this->cameraH = H;
    this->levelWidth = lW;
    this->levelHeight = lH;
}
Camera2::~Camera2() {}

void Camera2::set_position_cameraRect(int posX, int posY) {
    this->cameraRect.x = posX - (cameraW/2);
    this->cameraRect.y = posY - (cameraH/2);

    if(cameraRect.x < 0){
        cameraRect.x = 0;
    }
    if(cameraRect.y < 0) {
        cameraRect.y = 0;
    }
    if((cameraRect.x + cameraRect.w) >= (levelWidth)){
        cameraRect.x =levelWidth - cameraW;
    }
    if((cameraRect.y + cameraRect.h) >= (levelHeight)){
        cameraRect.y = levelHeight - cameraH;
    }
}

void Camera2::draw(Units_Protected &units, Game_map &game_map) {
    int limitXL = cameraRect.x - (cameraW/2);
    int limitXR = cameraRect.x + (cameraW/2);
    int limitYU = cameraRect.y - (cameraH/2);
    int limitYD = cameraRect.y + (cameraH/2);
    Unit *flag = factory.createUnit(COLORLESS_FLAG,1000,cameraRect.x,cameraRect.y);
    flag->set_pos_camera(cameraRect.x,cameraRect.y);
    flag->animate(cameraRect);
    game_map.draw_map(limitXL,limitXR,limitYU,limitYD,cameraRect);
    for (int i = 0; i <units.size() ; ++i) {
        if(BETWEEN(units[i]->get_posx(),limitXL,limitXR)){
            if(BETWEEN(units[i]->get_posy(),limitYU,limitYD)){
                units[i]->animate(cameraRect);
             }
        }
    }
}
