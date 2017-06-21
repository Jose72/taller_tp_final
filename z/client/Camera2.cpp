#include <zconf.h>
#include "Camera2.h"

#define BETWEEN(value, min, max) (((value) < (max)) && ((value) > (min)))

Camera2::Camera2(SDL_Surface *screen,int posX, int posY, int W, int H, int lW, int lH, Factory_Units &f):factory(f) {
    this->screen = screen;
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
    this->cameraRect.x = posX;
    this->cameraRect.y = posY;
    if (cameraRect.x < 0) {
        cameraRect.x = 0;
    }
    if (cameraRect.y < 0) {
        cameraRect.y = 0;
    }
    if ((cameraRect.x + cameraRect.w) >= (levelWidth)) {
        cameraRect.x = levelWidth - cameraW;
    }
    if ((cameraRect.y + cameraRect.h) >= (levelHeight)) {
        cameraRect.y = levelHeight - cameraH;
    }
}

void Camera2::draw(Units_Protected &units, Game_map &game_map, SoundManager &soundManager) {
    unsigned int ticks = SDL_GetTicks();
    if((ticks % 20 ) == 0) {
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
        int limitXL = cameraRect.x - (cameraW);
        int limitXR = cameraRect.x + (cameraW );
        int limitYU = cameraRect.y - (cameraH );
        int limitYD = cameraRect.y + (cameraH);
        game_map.draw_map(limitXL, limitXR, limitYU, limitYD, cameraRect);
        units.animate(limitXL, limitXR, limitYU, limitYD, cameraRect, soundManager);
    }
}

int Camera2::getPosCameraX() {
    return cameraRect.x;
}

int Camera2::getPosCameraY() {
    return cameraRect.y;
}
