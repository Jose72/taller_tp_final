#include <iostream>
#include "SDL.h"
#include "csprite.h"
#include "Animation.h"
#include "Game_map.h"
#include "Flag.h"
#include "Fort.h"
#include "Grunt.h"
#include "SelectionHandler.h"

#define IMAGEPATH "/home/matias/Escritorio/Client/sprites/robot1/1.bmp"

#define LEFT_BUTTON 3
#define RIGHT_BUTTON 1

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

    Animation animation(screen,IMAGEPATH,70,80);
    int posx1 = 100;
    int posy1 = 100;
    int posx2 = 400;
    int posy2 = 400;
    int destinox;
    int destinoy;
    int seleccionx;
    int selecciony;

    std::vector<Unit*> all_units;
    Game_map game_map(screen);
    Flag flag(screen,10,10);
    Fort fort(screen,400,0);
    Unit* grunt = new Grunt(screen,posx2,posy2);
    all_units.push_back(grunt);
    std::cout << all_units[0]->get_posx();

    Unit* grunt_prueba = new Grunt(screen,posx1,posy1);
    all_units.push_back(grunt_prueba);
    grunt_prueba->get_posx();

    SelectionHandler sHandler(all_units);

    SDL_Event event;

    //main application loop
    while(running == true){

        SDL_PollEvent(&event);
        Uint32 ticks = SDL_GetTicks();
        switch (event.type){
            case SDL_QUIT:
                running = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == LEFT_BUTTON){
                    destinox = event.button.x;
                    destinoy = event.button.y;
                    break;
                }
                if(event.button.button == RIGHT_BUTTON){
                    seleccionx = event.button.x;
                    selecciony = event.button.y;
                    sHandler.select_unit(seleccionx,selecciony);
                    break;
                }

        }

        if ((ticks % 10) == 0) {
            if (posx1 < destinox) {
                posx1 += 1;
            }
            if (posx1 > destinox) {
                posx1 -= 1;
            }
            if (posy1 < destinoy) {
                posy1 += 1;
            }
            if (posy1 > destinoy) {
                posy1 -= 1;
            }
        }/*
        if(sHandler.get_unit_s()!= NULL) {
            sHandler.get_unit_s()->set_pos(posx1,posy1);

        }
        */
        //grunt.set_pos(sHandler.get_unit_selected()->get_posx(),sHandler.get_unit_selected()->get_posy());
       //animation.animate(100,100);

        game_map.draw_map();
        flag.animate();
        fort.animate();
        //grunt_prueba->set_pos(posx,posy);
        for (int i = 0; i <all_units.size() ; ++i) {
            all_units[i]->set_pos(posx1,posy1);
            all_units[i]->animate();
        }


        SDL_Flip(screen);
    }
}