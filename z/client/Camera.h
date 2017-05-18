#ifndef CLIENT_CAMERA_H
#define CLIENT_CAMERA_H

#include <vector>
#include "Animation.h"
#include "Unit.h"
#include "Game_map.h"

class Camera {
private:
    int posCameraX;
    int posCameraY;
    int cameraW;
    int cameraH;

public:
    Camera(int posX, int posY, int W, int H);
    ~Camera();

    void set_camera_position(int posX, int posY);

    void show(std::vector<Unit*>&units, Game_map &game_map);

};


#endif //CLIENT_CAMERA_H
