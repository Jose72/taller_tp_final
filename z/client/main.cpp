#include <iostream>
#include "SDL.h"
#include "Animation.h"
#include "Game_map.h"
#include "SelectionHandler.h"
#include "Factory_Units.h"
#include "Camera.h"
#include "Socket.h"
#include "Thread.h"
#include "T_Client.h"
#include "TClient_receive.h"
#include "Units_Protected.h"

#define IMAGEPATH "client/sprites/robot1/1.bmp"

#define LEFT_BUTTON 3
#define RIGHT_BUTTON 1
#define WINDOW_H 600
#define WINDOW_W 800

int main(int argc, char *argv[]){
    SDL_Surface *screen;
    std::vector<Unit*> u;
    Units_Protected all_units(u);

    bool waiting_server = true;
    //INICIA SDL Y CREA LA PANTALLA
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        std::cout<<"No se puedo iniciar SDL\n"<< SDL_GetError();
        return 1;
    }
    screen = SDL_SetVideoMode(WINDOW_W, WINDOW_H, 32,SDL_HWSURFACE);
    if(screen == NULL){
        std::cout<<"No se puede inicializar el modo grafico\n" <<SDL_GetError();
    }
    atexit(SDL_Quit);
    SpritesPool pool(screen);
    Factory_Units factory(pool);
    tSocket socket;
    Game_map game_map(screen);
    int port_number = atoi(argv[2]);
    socket.connect(argv[1],port_number);
    std::vector<tThread*> threads;
    threads.push_back(new TClient_receive(socket,game_map,all_units,factory,waiting_server));
    threads[0]->start();
    bool running = true;

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

    Unit *grunt = factory.createUnit(BLUE_GRUNT,posx1,posy1);
    Unit *flag = factory.createUnit(COLORLESS_FLAG,posx2,posy2);
    Unit *fort = factory.createUnit(FORT,posx1,posy2);
    //all_units.push_back(grunt);
    //all_units.push_back(flag);
   // all_units.push_back(fort);

    //game_map.set_screen(screen);
    SDL_Event event;
    SelectionHandler sHandler;
    while(waiting_server){}
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
                    sHandler.set_destiny(destinox,destinoy);
                    break;
                }
                if(event.button.button == RIGHT_BUTTON){
                    seleccionx = event.button.x;
                    selecciony = event.button.y;
                    sHandler.set_location(seleccionx,selecciony,all_units);
                    break;
                }
        }

        sHandler.move_unit();
        camera.set_camera_position(posCameraX,posCameraY);
        camera.set_relative_position(all_units);

        camera.show(all_units, game_map);
        SDL_Flip(screen);
    }
    for (int i = 0; i <threads.size(); ++i) {
        threads[i]->join();

    }
}