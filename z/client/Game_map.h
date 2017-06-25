#ifndef CLIENT_GAME_MAP_H
#define CLIENT_GAME_MAP_H
#define N_TEXTURAS 5
#define MAP_LENGHT 1000


#include <vector>
#include "Animation.h"

class Game_map {
private:
    // 0 PRADERA
    // 1 AGUA
    // 2 LAVA
    // 3 NIEVE
    // 4 ASFALTO
    // 5 PANTANO
    // 6 TIERAA
    // 7 CARRETERA

    SDL_Surface *screen;
    Animation *tex0,*tex1,*tex2,*tex3,*tex4, *tex5, *tex6, *tex7;
    std::vector<int> map_des;

public:
    Game_map();
    Game_map(SDL_Surface *sc);
    ~Game_map();
    void add_tile(int tile);
    void draw_map(int limitXL, int limitXR, int limitYU, int limitYD, SDL_Rect &cameraRect);

private:
    void load_tex();

};


#endif //CLIENT_GAME_MAP_H
