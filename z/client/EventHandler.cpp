#include "EventHandler.h"
#include "../server/gameMap.h"

#define LEFT_BUTTON 3
#define RIGHT_BUTTON 1


EventHandler::EventHandler(SDL_Surface *screen,Camera &c, PlayerInterface &p, Units_Protected &u, tSocket &s, Game_map &m, bool &b):
        gameCamera(c),playerInterface(p),units(u),socket(s), gameMap(m),running(b){
    this->screen = screen;
}

EventHandler::~EventHandler() {}

void EventHandler::run() {
    SelectionHandler sHandler(socket);
    SDL_Event event;
    int posCameraX = gameCamera.get_camera_posX();
    int posCameraY = gameCamera.get_camera_posY();
    int destinoX, destinoY, seleccionX, seleccionY;
    while(running == true) {
        if (SDL_PollEvent(&event)) {
            SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
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
                            sHandler.set_destiny(destinoX, destinoY);
                            break;
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
        sHandler.move_unit();

        gameCamera.set_camera_position(posCameraX, posCameraY);
        gameCamera.set_relative_position(units);

        gameCamera.show(units, gameMap);
        playerInterface.show();
        SDL_Flip(screen);
    }
}

void EventHandler::stop() {
    socket.shutdown(SHUT_WR);
}