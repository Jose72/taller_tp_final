#include "Game_map.h"
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
    delete(tex0);
}

void Game_map::add_tile(int tile) {
   map_des.push_back(tile);
}

void Game_map::draw_map() {
    int i,j,x,y,t;
    //dibujar escenario
    for (i=0 ; i<10 ; i++) {
        for (j=0 ; j<10 ; j++) {
            int pos = ((i*10)+(j));
            t = this->map_des[pos];
            // calculo de la posición del tile
            x = j*32;
            y = i*32;
            switch (t) {
                case 0:
                    this->tex0->animate(x, y);
                    break;
                case 1:
                    this->tex1->animate(x, y);
                    break;
                case 2:
                    this->tex2->animate(x, y);
                    break;
                case 3:
                    this->tex3->animate(x, y);
                    break;
                case 4:
                    this->tex4->animate(x, y);
                    break;
                case 5:
                    this->tex5->animate(x,y);
                default:
                    break;
            }
        }
    }
}

void Game_map::draw_map(int limitXL, int limitXR, int limitYU, int limitYD) {

    int x,y,t;
    //dibujar escenario
    for (int i =limitYU ; i<limitYD; i++) {
        for (int j=limitXL ; j<limitXR; j++) {
            int pos = ((i*10)+(j));
            if(pos < MAP_LENGHT ){
                t = this->map_des[pos];
                // calculo de la posición del tile
                x = j*32;
                y = i*32;
                switch (t) {
                    case 0:
                        this->tex0->animate(x, y);
                        break;
                    case 1:
                        this->tex1->animate(x, y);
                        break;
                    case 2:
                        this->tex2->animate(x, y);
                        break;
                    case 3:
                        this->tex3->animate(x, y);
                        break;
                    case 4:
                        this->tex4->animate(x, y);
                        break;
                    case 5:
                        this->tex5->animate(x, y);
                        break;
                    default:
                        break;
                }
            }
        }
    }

}

// 1.BMP PASTO
// 2.BMP AGUA
// 3.BMP LAVA
// 4.BMP NIEVE
// 5.BMP RUTA
// 6.bmp ARENA
void Game_map::load_tex() {
    this->tex0 = new Animation(this->screen,"client/sprites/tiles/1.bmp",32,32);
    this->tex1 = new Animation(this->screen,"client/sprites/tiles/2.bmp",32,32);
    this->tex2 = new Animation(this->screen,"client/sprites/tiles/3.bmp",32,32);
    this->tex3 = new Animation(this->screen,"client/sprites/tiles/4.bmp",32,32);
    this->tex4 = new Animation(this->screen,"client/sprites/tiles/5.bmp",32,32);
    this->tex5 = new Animation(this->screen,"client/sprites/tiles/6.bmp",32,32);

}

void Game_map::set_screen(SDL_Surface *sc) {
    this->screen = sc;
}
