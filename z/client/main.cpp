#include <iostream>
#include "SDL.h"
#include "csprite.h"
#include "Animation.h"
#include "Game_map.h"
#include "flag.h"

#define IMAGEPATH "/home/matias/Escritorio/Client/sprites/robot1/1.bmp"

int main(int argc, char *argv[]){
    bool running = true;
    SDL_Surface *screen;

    if(SDL_Init(SDL_INIT_VIDEO)<0){
        std::cout<<"No se puedo iniciar SDL\n"<< SDL_GetError();
        return 1;
    }
    screen = SDL_SetVideoMode(800, 600, 32,SDL_HWSURFACE);
    if(screen == NULL){
        std::cout<<"No se puede inicializar el modo grafico\n" <<SDL_GetError();
    }
    atexit(SDL_Quit);

    Animation animation(screen,IMAGEPATH,70,80,0);

    Game_map game_map(screen);
    Flag flag(screen,10,10);

    SDL_Event occur;

    //main application loop
    while(running == true){

        SDL_PollEvent(&occur);
        if(occur.type == SDL_QUIT){
            running = false;
        }
       //animation.animate(100,100);
        game_map.draw_map();
        flag.animate_flag();




        SDL_Flip(screen);
    }

}