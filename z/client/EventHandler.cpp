#include "EventHandler.h"
#include "../server/gameMap.h"
#include "Camera2.h"

#define LEFT_BUTTON 1
#define RIGHT_BUTTON 3
#define WINDOW_H 800
#define WINDOW_W 600


EventHandler::EventHandler(SDL_Surface *screen,PlayerInterface &p, Units_Protected &u, tSocket &s, Game_map &m, bool &b, Factory_Units &f):
        playerInterface(p),units(u),socket(s), gameMap(m),running(b), factory(f){
    this->screen = screen;
}

EventHandler::~EventHandler() {}

void EventHandler::run() {
    Protocol protocol(socket,units,gameMap,factory);
    SelectionHandler sHandler(protocol);
    SDL_Event event;
    int posCameraX = 0;
    int posCameraY = 0;
    Camera2 camera2(posCameraX,posCameraY,480,240,WINDOW_W,WINDOW_H,factory);
    int destinoX, destinoY, seleccionX, seleccionY;
    while(running == true) {
        //MOSTRAR
        camera2.set_position_cameraRect(posCameraX,posCameraY);
        camera2.draw(units,gameMap);
        playerInterface.show();
        SDL_Flip(screen);
        //MOSTRAR
        if (SDL_PollEvent(&event)) {
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
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
                case SDL_MOUSEBUTTONDOWN:
                    if (!playerInterface.checkClickedButtons(event.button.x, event.button.y)) {
                        if (event.button.button == LEFT_BUTTON) {
                            destinoX = event.button.x;
                            destinoY = event.button.y;
                            sHandler.set_objetive(destinoX, destinoY,units);
                            break;
                            //SDL_Quit()
                        }
                        if (event.button.button == RIGHT_BUTTON) {
                            seleccionX = event.button.x;
                            seleccionY = event.button.y;
                            sHandler.set_location(seleccionX, seleccionY, units);
                            break;
                        }
                    }
            }
        }
        //camera2.update_pos();
    }
}

void EventHandler::stop() {
    socket.shutdown(SHUT_WR);
}