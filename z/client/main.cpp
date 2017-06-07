#include <iostream>
#include <SDL_ttf.h>
#include "SDL.h"
#include "Animation.h"
#include "Game_map.h"
#include "SelectionHandler.h"
#include "Factory_Units.h"
#include "../common/Socket.h"
#include "../common/Thread.h"
#include "T_Client.h"
#include "TClient_receive.h"
#include "Units_Protected.h"
#include "ClickableButton.h"
#include "PlayerInterface.h"
#include "EventHandler.h"
#define IMAGEPATH "client/sprites/robot1/1.bmp"

#define LEFT_BUTTON 3
#define RIGHT_BUTTON 1
#define WINDOW_H 800
#define WINDOW_W 600
#define PLAYER_INTERFACE_W 300

int main(int argc, char *argv[]){
    SDL_Surface *screen;
    std::vector<Unit*> u;
    std::map<int, Unit*>um;
    Units_Protected all_units(um);
    bool running = true;

    bool waiting_server = true;
    //INICIA SDL Y CREA LA PANTALLA
    if(SDL_Init(SDL_INIT_VIDEO)<0){
        std::cout<<"No se puedo iniciar SDL\n"<< SDL_GetError();
        return 1;
    }

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) ){
        std::cout<< "No se pudo iniciar SDL_image Error:" << IMG_GetError() << std::endl;
        return 2;
    }

    if(TTF_Init()==-1) {
        std::cout<< "No se pudo iniciar TTF_Init:" << TTF_GetError() << std::endl;
        return 3;
    }

    screen = SDL_SetVideoMode(WINDOW_W + PLAYER_INTERFACE_W, WINDOW_H, 32,SDL_HWSURFACE);
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
    threads.push_back(new TClient_receive(socket,game_map,all_units,factory,waiting_server, running));
    threads[0]->start();
    Protocol protocol(socket,all_units,game_map,factory);

    int posx1 = 100;
    int posy1 = 100;
    int posx2 = 400;
    int posy2 = 400;
    int posCameraX = 200;
    int posCameraY = 200;
    SDL_Rect cameraRect = {0,0,640,480};

    SelectionHandler sHandler(protocol);
    PlayerInterface playerInterface(screen,&sHandler,WINDOW_W,WINDOW_H,PLAYER_INTERFACE_W);

    while(waiting_server){}
    //main application loop

    threads.push_back(new EventHandler(screen,playerInterface,all_units,socket, game_map, running,factory));
    threads[1]->start();

    for (int i = 0; i <threads.size(); ++i) {
        threads[i]->join();

    }
    TTF_Quit();
    IMG_Quit();

}