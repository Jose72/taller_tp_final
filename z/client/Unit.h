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

enum Attack_Direction{
    ZERO_A = 0,
    ONE_A = 45,
    TWO_A = 90,
    THREE_A = 135,
    FOUR_A = 180,
    FIVE_A = 225,
    SIX_A = 270,
    SEVEN_A = 315
};

enum State{
    MOVING,
    ATTACKING,
    DEAD,
    DRINKING,
    CELEBRATE,
    COLORLESS,
    BLUE,
    GREEN,
    RED,
    YELLOW,
    ROLLING
};

class Unit {
protected:
    int posx;
    int posy;
    int cod_unit;
    int health;
    int posxO;
    int posyO;
    int posX_attack;
    int posY_attack;
    int cameraPosX;
    int cameraPosY;
    Direction  direction;
    Attack_Direction attack_direction;
    State state;
    int current_frame;
    std::vector<Animation *> &animation;
    std::vector<Animation *> &animation2;
    std::vector<Animation *> &animation3;
    std::vector<Animation *> &animation4;
    std::vector<Animation *> &animation5;

public:
    Unit(std::vector<Animation *> &a0,
         std::vector<Animation *> &a1,
         std::vector<Animation *> &a2,
         std::vector<Animation *> &a3,
         std::vector<Animation *> &a4,
         int cu, int posx, int posy);

    Unit(std::vector<Animation *> &a0,
         std::vector<Animation *> &a1,
         std::vector<Animation *> &a2,
         std::vector<Animation *> &a3,
         std::vector<Animation *> &a4,
         int cu, int posx, int posy, State state);
    ~Unit();
    void animate(SDL_Rect &cameraRect);
    void set_pos(int x,int y);
    void set_pos_camera(int x, int y);
    int get_cameraPosX();
    int get_cameraPosY();
    int get_posx();
    int get_posy();
    int get_unit_code();
    void animate_static(SDL_Rect &cameraRect, std::vector<Animation*> &a, int max_frame);
    void animate_moving(SDL_Rect &cameraRect, std::vector<Animation*> &a, int max_frame);
    void animate_attacking(SDL_Rect &cameraRect, std::vector<Animation*> &a, int max_frame);
    void animate_attack(SDL_Rect &cameraRect);
    void set_state(State s);
    State get_state();
    void set_health(int health);
    int get_heatlh();
    void set_attack(int posX, int posY);
};


#endif //CLIENT_UNIT_H
