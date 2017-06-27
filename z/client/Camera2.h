//
// Created by matias on 30/05/17.
//

#ifndef Z_CAMERA2_H
#define Z_CAMERA2_H


#include <SDL_video.h>
#include "Units_Protected.h"
#include "Game_map.h"
#include "Factory_Units.h"

class Camera2 {
private:
    SDL_Surface *screen;
    SDL_Rect cameraRect;
    int posCameraRectX;
    int posCameraRectY;
    int cameraW;
    int cameraH;
    int levelWidth;
    int levelHeight;
    Factory_Units &factory;
    bool movingLeft;
    bool movingRight;
    bool movingUp;
    bool movingDown;


public:
    Camera2(SDL_Surface *screen,int posX, int posY, int W, int H, int lW, int lH, Factory_Units &f);
    ~Camera2();
    void draw(Units_Protected &units, Game_map &game_map,SoundManager &soundManager);
    int getPosCameraX();
    int getPosCameraY();
    void startMovingRight();
    void stopMovingRight();
    void startMovingLeft();
    void stopMovingLeft();
    void startMovingUp();
    void stopMovingUp();
    void startMovingDown();
    void stopMovingDown();

    void updateCameraPos();




};


#endif //Z_CAMERA2_H
