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
#define MOVE_MOUSE_LIMIT 32

EventHandler::EventHandler(SDL_Surface *screen,
                           PlayerInterface &p,
                           Units_Protected &u,
                           tSocket &s,
                           Game_map &m,
                           bool &b,
                           Factory_Units &f,
                           int &id, TechLevelProtected &tech,WinnerProtected &winner,
                            SoundManager &soundManager):
        playerInterface(p),units(u),socket(s), gameMap(m),running(b), factory(f), id_client(id), techLevel(tech), winner(winner),soundManager(soundManager){
    this->screen = screen;
}

EventHandler::~EventHandler() {}

void EventHandler::run() {
    Protocol protocol(socket,units,gameMap,factory, techLevel,winner,soundManager);

    SDL_Event event;
    Unit* fortPlayer = units.getFortPlayer(id_client);
    int posCameraX = fortPlayer->get_posx();
    int posCameraY = fortPlayer->get_posy();

    Camera2 camera2(screen,posCameraX,posCameraY,CAMERADX,CAMERADY,WINDOW_W,WINDOW_H,factory);
    SelectionHandler sHandler(protocol,id_client,camera2);
    int destinoX, destinoY, seleccionX, seleccionY;
    int selectionStartX;
    int selectionStartY;
    int selectionEndX;
    int selectionEndY;

    while(running == true) {
        //MOSTRAR
        camera2.updateCameraPos();
        //camera2.set_position_cameraRect(posCameraX,posCameraY);
        posCameraX = camera2.getPosCameraX();
        posCameraY = camera2.getPosCameraY();
        camera2.draw(units,gameMap,soundManager);
        playerInterface.show(sHandler, techLevel,winner,id_client);
        SDL_Flip(screen);


        //MOSTRAR
        while (SDL_PollEvent(&event)) {

            switch (event.type) {
                case SDL_QUIT:
                    SDL_Quit();
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                            camera2.startMovingLeft();
                            break;
                        case SDLK_RIGHT:
                            camera2.startMovingRight();
                            break;
                        case SDLK_UP:
                            camera2.startMovingUp();
                            break;
                        case SDLK_DOWN:
                            camera2.startMovingDown();
                            break;
                    }
                    break;

                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                            camera2.stopMovingLeft();
                            break;
                        case SDLK_RIGHT:
                            camera2.stopMovingRight();
                            break;
                        case SDLK_UP:
                            camera2.stopMovingUp();
                            break;
                        case SDLK_DOWN:
                            camera2.stopMovingDown();
                            break;
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (!playerInterface.checkClickedButtons(event.button.x, event.button.y,protocol)) {
                        if (event.button.button == LEFT_BUTTON) {
                            destinoX = event.button.x + camera2.getPosCameraX();
                            destinoY = event.button.y + camera2.getPosCameraY();
                            std::cout << "X: "<< destinoX << " Y: " << destinoY <<"\n";
                            sHandler.set_target(destinoX, destinoY,units);
                            break;
                            //SDL_Quit()
                        }
                        if (event.button.button == RIGHT_BUTTON) {
                            selectionStartX =event.button.x + camera2.getPosCameraX();
                            selectionStartY = event.button.y + camera2.getPosCameraY();
                            break;
                        }
                    }
                case SDL_MOUSEBUTTONUP:
                    if (!playerInterface.checkClickedButtons(event.button.x, event.button.y,protocol)) {
                        if (event.button.button == RIGHT_BUTTON) {
                            selectionEndX = event.button.x + camera2.getPosCameraX();
                            selectionEndY = event.button.y + camera2.getPosCameraY();
                            sHandler.selectUnits(selectionStartX,selectionEndX,selectionStartY,selectionEndY,units);
                            if(sHandler.unit_select()){
                                soundManager.play((int) sHandler.getUnit()->get_type());
                            }
                            break;
                        }
                    }
                case SDL_MOUSEMOTION:
                    if((event.motion.y < (MOVE_MOUSE_LIMIT)) &&(event.motion.y > 0)){
                        camera2.startMovingUp();
                    } else{
                        camera2.stopMovingUp();
                    }

                    if((event.motion.y > (CAMERADY-MOVE_MOUSE_LIMIT)) && (event.motion.y <CAMERADY)){
                        camera2.startMovingDown();
                    }else{
                        camera2.stopMovingDown();
                    }

                    if((event.motion.x < (MOVE_MOUSE_LIMIT)) && (event.motion.x >0)){
                        camera2.startMovingLeft();
                    }else {
                        camera2.stopMovingLeft();
                    }

                    if((event.motion.x > (CAMERADX-MOVE_MOUSE_LIMIT)) && (event.motion.x <CAMERADX)){
                        camera2.startMovingRight();
                    } else{
                        camera2.stopMovingRight();
                    }
            }
        }
        checkDead();
        //SDL_Delay((1000/10 )-(SDL_GetTicks()-ticks));
        //camera2.update_pos();
    }
}

void EventHandler::stop() {
    socket.shutdown(SHUT_WR);
}

void EventHandler::checkDead() {
    unsigned int ticks = SDL_GetTicks();
    if((ticks %100) == 0){
        units.cleanDeadUnits();
    }
}
