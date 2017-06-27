#include <cmath>
#include "Game_map.h"

#define BETWEEN(value, min, max) (((value) < (max)) && ((value) > (min)))


Game_map::Game_map() {
    this->load_tex();
}

Game_map::Game_map(SDL_Surface *sc) {
    this->screen = sc;
    this->load_tex();
}
Game_map::~Game_map() {
    delete(tex1);
    delete(tex2);
    delete(tex3);
    delete(tex4);
    delete(tex5);
    delete(tex6);
    delete(tex7);
    delete(tex0);
}

void Game_map::add_tile(int tile) {
   map_des.push_back(tile);
}

void Game_map::draw_map(int limitXL, int limitXR, int limitYU, int limitYD, SDL_Rect &cameraRect) {
    int mapDimensions = sqrt(map_des.size());
    int x,y,t;

    for (int i =0 ; i < mapDimensions; i++) {
        for (int j=0 ; j < mapDimensions; j++) {
            unsigned int pos = ((i*mapDimensions)+(j));
            if(pos < map_des.size()){
                t = this->map_des[pos];
                // calculo de la posición del tile
                x = j*32;
                y = i*32;
                if (BETWEEN(x,limitXL,limitXR)){
                    if(BETWEEN(y,limitYU,limitYD)){
                        switch (t) {
                            case 0:
                                this->tex0->animate(x, y,cameraRect);
                                break;
                            case 1:
                                this->tex1->animate(x, y,cameraRect);
                                break;
                            case 2:
                                this->tex2->animate(x, y,cameraRect);
                                break;
                            case 3:
                                this->tex3->animate(x, y,cameraRect);
                                break;
                            case 4:
                                this->tex4->animate(x, y,cameraRect);
                                break;
                            case 5:
                                this->tex5->animate(x, y,cameraRect);
                                break;
                            case 6:
                                this->tex6->animate(x, y,cameraRect);
                                break;
                            case 7:
                                this->tex7->animate(x, y,cameraRect);
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
        }
    }

}

// 1.BMP PRADERA
// 2.BMP AGUA
// 3.BMP LAVA
// 4.BMP NIEVE
// 5.BMP RUTA
// 6.bmp PANTANO
// 7.bmp TIERRA
// 8.BMP CARRETERA
void Game_map::load_tex() {
    this->tex0 = new Animation(this->screen,"client/sprites/tiles/1.bmp",32,32);
    this->tex1 = new Animation(this->screen,"client/sprites/tiles/2.bmp",32,32);
    this->tex2 = new Animation(this->screen,"client/sprites/tiles/3.bmp",32,32);
    this->tex3 = new Animation(this->screen,"client/sprites/tiles/4.bmp",32,32);
    this->tex4 = new Animation(this->screen,"client/sprites/tiles/5.bmp",32,32);
    this->tex5 = new Animation(this->screen,"client/sprites/tiles/6.bmp",32,32);
    this->tex6 = new Animation(this->screen,"client/sprites/tiles/7.bmp",32,32);
    this->tex7 = new Animation(this->screen,"client/sprites/tiles/8.bmp",32,32);

}


