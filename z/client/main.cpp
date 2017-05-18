#include <iostream>
#include "SDL.h"
#include "Animation.h"
#include "Game_map.h"
#include "Fort.h"
#include "SelectionHandler.h"
#include "Factory_Units.h"
#include "Camera.h"

#define IMAGEPATH "client/sprites/robot1/1.bmp"

#define LEFT_BUTTON 3
#define RIGHT_BUTTON 1
#define WINDOW_H 600
#define WINDOW_W 800

int main(int argc, char *argv[]){
    bool running = true;
    SDL_Surface *screen;

    if(SDL_Init(SDL_INIT_VIDEO)<0){
        std::cout<<"No se puedo iniciar SDL\n"<< SDL_GetError();
        return 1;
    }
    screen = SDL_SetVideoMode(WINDOW_W, WINDOW_H, 32,SDL_HWSURFACE);
    if(screen == NULL){
        std::cout<<"No se puede inicializar el modo grafico\n" <<SDL_GetError();
    }
    atexit(SDL_Quit);

    int posx1 = 100;
    int posy1 = 100;
    int posx2 = 400;
    int posy2 = 400;
    int posCameraX = 500;
    int posCameraY = 500;
    int destinox;
    int destinoy;
    int seleccionx;
    int selecciony;
    Camera camera(posCameraX,posCameraY,WINDOW_W,WINDOW_H);
    SpritesPool pool(screen);
    Factory_Units factory(pool);
    Unit *grunt = factory.createUnit(BLUE_GRUNT,posx1,posy1);
    Unit *flag = factory.createUnit(COLORLESS_FLAG,posx2,posy2);
    std::vector<Unit*> all_units;
    all_units.push_back(grunt);
    all_units.push_back(flag);
    Game_map game_map(screen);
    game_map.load_configuration();

    /*
    std::vector<Unit*> all_units;
    Flag flag(screen,10,10);
    Fort fort(screen,400,0);
    Unit* grunt = new Grunt(screen,posx2,posy2);
    all_units.push_back(grunt);
    std::cout << all_units[0]->get_posx();
    Unit* grunt_prueba = new Grunt(screen,posx1,posy1);
    all_units.push_back(grunt_prueba);
    grunt_prueba->get_posx();
    SelectionHandler sHandler(all_units);
     */

    SDL_Event event;

    //main application loop
    while(running == true){
        SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,0,0,0));
        SDL_PollEvent(&event);
        Uint32 ticks = SDL_GetTicks();
        switch (event.type){
            case SDL_QUIT:
                running = false;
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym){
                    case SDLK_LEFT:
                        posCameraX--;
                        break;
                    case SDLK_RIGHT:
                        posCameraX++;
                        break;
                    case SDLK_UP:
                        posCameraY--;
                        break;
                    case SDLK_DOWN:
                        posCameraY++;
                        break;
                }
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
                    //sHandler.select_unit(seleccionx,selecciony);
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
        }
        grunt->set_pos(posx1,posy1);
        camera.set_camera_position(posCameraX,posCameraY);
        /*
        if(sHandler.get_unit_s()!= NULL) {
            sHandler.get_unit_s()->set_pos(posx1,posy1);

        }
        */
        //grunt.set_pos(sHandler.get_unit_selected()->get_posx(),sHandler.get_unit_selected()->get_posy());
       //animation.animate(posCameraX,posCameraY);


        //game_map.draw_map();
        /*
        flag->animate();
        grunt->animate();
         */
        camera.show(all_units, game_map);

        /*
        //grunt_prueba->set_pos(posx,posy);
        for (int i = 0; i <all_units.size() ; ++i) {
            all_units[i]->set_pos(posx1,posy1);
            all_units[i]->animate();
        }
        */


        SDL_Flip(screen);
    }
}