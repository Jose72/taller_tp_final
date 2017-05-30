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
    SDL_Rect cameraRect;
    int posCameraRectX;
    int posCameraRectY;
    int cameraW;
    int cameraH;
    int levelWidth;
    int levelHeight;
    Factory_Units &factory;


public:
    Camera2(int posX, int posY, int W, int H, int lW, int lH, Factory_Units &f);
    ~Camera2();
    void set_position_cameraRect(int posX, int posY);
    void draw(Units_Protected &units, Game_map &game_map);



};


#endif //Z_CAMERA2_H
