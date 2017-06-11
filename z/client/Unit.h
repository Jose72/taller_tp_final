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
    MOVING1,
    ATTACKING1,
    CELEBRATE,
    DRINKING,
    DEAD1,
    DEAD2,
    COLORLESS,
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
    int owner;
    Direction  direction;
    Attack_Direction attack_direction;
    State state;
    int current_frame;
    int maxFrame1;
    int maxFrame2;
    int maxFrame3;
    int maxFrame4;
    int maxFrame5;
    std::vector<Animation *> &animation;
    std::vector<Animation *> &animation2;
    std::vector<Animation *> &animation3;
    std::vector<Animation *> &animation4;
    std::vector<Animation *> &animation5;
    FlagsUnitType unitType;

public:
    Unit(std::vector<Animation *> &a0,
         std::vector<Animation *> &a1,
         std::vector<Animation *> &a2,
         std::vector<Animation *> &a3,
         std::vector<Animation *> &a4,
         int cu, int posx, int posy,
         State state,
         FlagsUnitType unitType, int owner);
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
    void set_state(State s);
    State get_state();
    void set_health(int health);
    int get_heatlh();
    void set_attack(int posX, int posY);
    int get_owner();
    void set_owner(int owner);
    FlagsUnitType get_type();
};


#endif //CLIENT_UNIT_H
