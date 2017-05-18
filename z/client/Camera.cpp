#include "Camera.h"

#define BETWEEN(value, min, max) (((value) < (max)) && ((value) > (min)))


Camera::Camera(int posX, int posY, int W, int H) {
    this->posCameraX = posX;
    this->posCameraY = posY;
    this->cameraW = W;
    this->cameraH = H;
}

Camera::~Camera() {}

void Camera::set_camera_position(int posX, int posY) {
    if((posX > 0)){
        this->posCameraX = posX;
    }
    if(posY > 0){
        this->posCameraY = posY;
    }
}

void Camera::show(std::vector<Unit *> &units, Game_map &game_map) {
    int limitXL = this->posCameraX - this->cameraW;
    if(limitXL <0){
        limitXL = 0;
    }
    int limitXR = this->posCameraX + this->cameraW;
    int limitYU = this->posCameraY - this->cameraH;
    if(limitYU < 0){
        limitYU = 0;
    }
    int limitYD = this->posCameraY + this->cameraH;
    game_map.draw_map(limitXL,limitXR,limitYU,limitYD);
    for (int i = 0; i <units.size() ; ++i) {
        if(BETWEEN(units[i]->get_posx(),limitXL,limitXR)){
            if(BETWEEN(units[i]->get_posy(),limitYU,limitYD)){
                units[i]->animate();
            }
        }

    }

}

