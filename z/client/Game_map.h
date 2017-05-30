#ifndef CLIENT_GAME_MAP_H
#define CLIENT_GAME_MAP_H
#define N_TEXTURAS 5
#define MAP_LENGHT 1000


#include <vector>
#include "Casillas.h"
#include "Animation.h"

class Game_map {
private:
    // 0 PRADERA
    // 1 AGUA
    // 2 LAVA
    // 3 NIEVE
    // 4 ASFALTO
    // 5 PANTANO

    //AGREGAR COD PARA LAS TEXTURAS FALTANTES

    // TIERRA PRADERA NIEVE AGUA PANTANO LAVA CARRETERA ASFALTO
    SDL_Surface *screen;
    Animation *tex0,*tex1,*tex2,*tex3,*tex4, *tex5;
    //int map_descriptor[MAP_LENGHT];
    std::vector<int> map_des;
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
    Game_map();
    Game_map(SDL_Surface *sc);
    ~Game_map();
    void add_tile(int tile);
    void draw_map(SDL_Rect &cameraRect);
    void draw_map(int limitXL, int limitXR, int limitYU, int limitYD, SDL_Rect &cameraRect);
    void set_screen(SDL_Surface *sc);

private:
    void load_tex();

};


#endif //CLIENT_GAME_MAP_H
