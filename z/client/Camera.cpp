#include <iostream>
#include "Camera.h"
#include "Factory_Units.h"

#define BETWEEN(value, min, max) (((value) < (max)) && ((value) > (min)))


Camera::Camera(int posX, int posY, int W, int H, Factory_Units &factory): factory(factory) {
    this->posCameraX = posX;
    this->posCameraY = posY;
    this->cameraW = W;
    this->cameraH = H;
}

Camera::~Camera() {}

void Camera::set_camera_position(int posX, int posY) {
    this->posCameraXOld = this->posCameraX;
    this->posCameraX = posX;
    this->posCameraYOld = this->posCameraY;
    this->posCameraY = posY;
}

void Camera::show(Units_Protected &units, Game_map &game_map) {
    int limitXL = this->posCameraX - (this->cameraW);

    int limitXR = this->posCameraX + (this->cameraW);
    int limitYU = this->posCameraY - (this->cameraH);
    int limitYD = this->posCameraY + (this->cameraH);
    Unit *flag = factory.createUnit(COLORLESS_FLAG,posCameraX,posCameraY);
    flag->set_pos_camera(posCameraX,posCameraY);
    flag->animate();
    game_map.draw_map(limitXL,limitXR,limitYU,limitYD);
    for (int i = 0; i <units.size() ; ++i) {
        /** if(BETWEEN(units[i]->get_cameraPosX(),limitXL,limitXR)){
             if(BETWEEN(units[i]->get_cameraPosY(),limitYU,limitYD)){
                 units[i]->animate();
             }
         }*/
        if(units[i]->get_cameraPosX() >= limitXL && units[i]->get_cameraPosX() <= limitXR){
            if(units[i]->get_cameraPosY() >= limitYU && units[i]->get_cameraPosY() <= limitYD){
                units[i]->animate();
            }
        }

    }

}

void Camera::set_relative_position(Units_Protected &units) {
    for (int i = 0; i <units.size() ; ++i) {
        int posUnitX = units[i]->get_posx();
        int posUnitY = units[i]->get_posy();
        //sin este if se muestra el grunt al iniciar el juego
        //se podria quitar si solamente se llega a este codigo al modificar la camara
        // if((posCameraX != posCameraXOld) || (posCameraY != posCameraYOld)) {
        int posRUniX = posUnitX + posCameraX;
        int posRUniY = posUnitY + posCameraY;

        // std::cout << posRUniX << "\n";
        // std::cout << posRUniY << "\n";
        /** if ((posRUniX < 0) && (posRUniY < 0)) {
             posUnitX = posUnitX + 20;
             posUnitY = posUnitY + 20;
         } else if ((posRUniX < 0) && (posRUniY > 0)) {
             posUnitX = posUnitX + 20;
             posUnitY = posUnitY - 20;
         } else if ((posRUniX > 0) && (posRUniY > 0)) {
             posUnitX = posUnitX - 20;
             posUnitY = posUnitY - 20;
         } else if ((posRUniX > 0) && (posRUniY < 0)) {
             posUnitX = posUnitX - 20;
             posUnitY = posUnitY + 20;
         }**/
        units[i]->set_pos_camera(posRUniX,posRUniY);

        // }
        //units[i]->set_pos(posUnitX,posUnitY);

    }
}

int Camera::get_camera_posX() {
    return this->posCameraX;
}

int Camera::get_camera_posY() {
    return this->posCameraY;
}