#ifndef CLIENT_CAMERA_H
#define CLIENT_CAMERA_H

#include <vector>
#include "Animation.h"
#include "Unit.h"
#include "Game_map.h"
#include "Units_Protected.h"
#include "Factory_Units.h"

class Camera {
private:
    int posCameraX;
    int posCameraY;
    int posCameraXOld;
    int posCameraYOld;
    int cameraW;
    int cameraH;
    Factory_Units &factory;

public:
    Camera(int posX, int posY, int W, int H, Factory_Units &factory_units);
    ~Camera();

    void set_camera_position(int posX, int posY);

    void show(Units_Protected &units, Game_map &game_map);

    void set_relative_position(Units_Protected &units);

    int get_camera_posX();
    int get_camera_posY();

};


#endif //CLIENT_CAMERA_H
