#ifndef CLIENT_UNIT_H
#define CLIENT_UNIT_H

#include <SDL_video.h>
#include <vector>
#include "Animation.h"
#include "SpritesPool.h"

enum Direction{
    ZERO = 0,
    ONE = 45,
    TWO = 90,
    THREE = 135,
    FOUR = 180,
    FIVE = 225,
    SIX = 270,
    SEVEN = 315
};

class Unit {
protected:
    int posx;
    int posy;
    int posxO;
    int posyO;
    int cameraPosX;
    int cameraPosY;
    Direction  direction;
    int current_frame;
    std::vector<Animation *> animation;
public:

    Unit( std::vector<Animation *> animation, int posx, int posy);
    ~Unit();
    void animate();
    void set_pos(int x,int y);
    void set_pos_camera(int x, int y);
    int get_cameraPosX();
    int get_cameraPosY();
    int get_posx();
    int get_posy();





};


#endif //CLIENT_UNIT_H
