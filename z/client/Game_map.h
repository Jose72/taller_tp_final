#ifndef CLIENT_GAME_MAP_H
#define CLIENT_GAME_MAP_H
#define N_TEXTURAS 5
#define MAP_LENGHT 1000


#include <vector>
#include "Casillas.h"
#include "Animation.h"

class Game_map {
private:
    // 0 PASTO
    // 1 AGUA
    //2 LAVA
    // 3 NIEVE
    // 4 RUTA
    SDL_Surface *screen;
    Animation *tex0,*tex1,*tex2,*tex3,*tex4, *tex5;
    int map_descriptor[MAP_LENGHT];
    /*
    int map_descriptor[MAP_LENGHT] = {0,0,0,0,0,0,0,0,0,0,
                                       0,0,0,0,0,0,0,0,0,0,
                                       0,1,0,0,3,0,0,2,0,0,
                                       4,1,4,5,3,4,4,2,4,4,
                                       4,1,4,5,3,4,4,2,4,4,
                                       4,1,4,5,3,4,4,2,4,4,
                                       4,1,4,5,3,4,4,2,4,4,
                                       0,1,0,5,3,0,0,2,0,0,
                                       0,0,0,0,0,0,0,0,0,0,
                                       0,0,0,0,0,0,0,0,0,0};
                                       */


public:
    Game_map(SDL_Surface *sc);
    ~Game_map();
    void load_configuration();
    void draw_map();
    void draw_map(int limitXL, int limitXR, int limitYU, int limitYD);

private:
    void load_tex();

};


#endif //CLIENT_GAME_MAP_H
