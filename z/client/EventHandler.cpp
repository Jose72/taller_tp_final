#include <iostream>
#include <SDL_mixer.h>
#include "EventHandler.h"
#include "../server/gameMap.h"
#include "Camera2.h"
#include "SoundManager.h"
#define LEFT_BUTTON 3
#define RIGHT_BUTTON 1
#define WINDOW_H 960
#define WINDOW_W 960
#define CAMERADX 600
#define CAMERADY 600

EventHandler::EventHandler(SDL_Surface *screen,
                           PlayerInterface &p,
                           Units_Protected &u,
                           tSocket &s,
                           Game_map &m,
                           bool &b,
                           Factory_Units &f,
                           int &id, TechLevelProtected &tech,WinnerProtected &winner):
        playerInterface(p),units(u),socket(s), gameMap(m),running(b), factory(f), id_client(id), techLevel(tech), winner(winner){
    this->screen = screen;
}

EventHandler::~EventHandler() {}

void EventHandler::run() {
    Protocol protocol(socket,units,gameMap,factory, techLevel,winner);

    SDL_Event event;
    int posCameraX = 0;
    int posCameraY = 0;
    Camera2 camera2(screen,posCameraX,posCameraY,CAMERADX,CAMERADY,WINDOW_W,WINDOW_H,factory);
    SelectionHandler sHandler(protocol,id_client,camera2);
    int destinoX, destinoY, seleccionX, seleccionY;
    SoundManager soundManager;
    while(running == true) {
        //MOSTRAR
        camera2.set_position_cameraRect(posCameraX,posCameraY);
        posCameraX = camera2.getPosCameraX();
        posCameraY = camera2.getPosCameraY();
        camera2.draw(units,gameMap);
        playerInterface.show(sHandler, techLevel,winner,id_client);
        SDL_Flip(screen);


        //MOSTRAR
        if (SDL_PollEvent(&event)) {

            switch (event.type) {
                case SDL_QUIT:
                    SDL_Quit();
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                            //camera2.startMovingLeft()
                            posCameraX = posCameraX -20;
                            break;
                        case SDLK_RIGHT:
                            posCameraX = posCameraX + 20;
                            break;
                        case SDLK_UP:
                            posCameraY = posCameraY - 20;
                            break;
                        case SDLK_DOWN:
                            posCameraY = posCameraY + 20;
                            break;
                    }
                    break;
                    /*
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                           // camera2.stopMovingLeft()
                            posCameraX = posCameraX -20;
                            break;
                        case SDLK_RIGHT:
                            posCameraX = posCameraX + 20;
                            break;
                        case SDLK_UP:
                            posCameraY = posCameraY - 20;
                            break;
                        case SDLK_DOWN:
                            posCameraY = posCameraY + 20;
                            break;
                    }
                    break;
                     */
                case SDL_MOUSEBUTTONDOWN:
                    if (!playerInterface.checkClickedButtons(event.button.x, event.button.y,protocol)) {
                        if (event.button.button == LEFT_BUTTON) {
                            destinoX = event.button.x + camera2.getPosCameraX();
                            destinoY = event.button.y + camera2.getPosCameraY();
                            std::cout << "X: "<< destinoX << " Y: " << destinoY <<"\n";
                            sHandler.set_objetive(destinoX, destinoY,units);
                            break;
                            //SDL_Quit()
                        }
                        if (event.button.button == RIGHT_BUTTON) {
                            seleccionX = event.button.x + camera2.getPosCameraX();
                            seleccionY = event.button.y + camera2.getPosCameraY();
                            std::cout << "X: "<< seleccionX << " Y: " << seleccionY <<"\n";
                            sHandler.set_location(seleccionX, seleccionY, units);
                            if(sHandler.unit_select()){
                                soundManager.play((int) sHandler.getUnit()->get_type());
                            }
                            break;
                        }
                    }
            }
        }
        checkDead();
        //camera2.update_pos();
    }
}

void EventHandler::stop() {
    socket.shutdown(SHUT_WR);
}

void EventHandler::checkDead() {
    unsigned int ticks = SDL_GetTicks();
    if((ticks %600) == 0){
        units.cleanDeadUnits();
    }
}