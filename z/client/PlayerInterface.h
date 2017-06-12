//
// Created by mbataglia on 22/05/17.
//

#ifndef Z_PLAYERINTERFACE_H
#define Z_PLAYERINTERFACE_H


#include <SDL_video.h>
#include <SDL_image.h>
#include "Animation.h"
#include "SelectionHandler.h"
#include "TTF_Writter.h"
#include "Drawer.h"
#include "ClickableButton.h"

class PlayerInterface {
private:
    SDL_Surface * screen;
    int gameWidth;
    int gameHeight;
    int width;
    Animation *background;
    Drawer drawer;
    std::vector<ClickableButton*> buttons;
public:
    PlayerInterface(SDL_Surface* screen,
                        int gameWidth,
                        int gameHeight,
                        int width);

    void show(SelectionHandler selectionHandler, TechLevelProtected &techProtected);

    virtual ~PlayerInterface();

    int getCol(int division, int offset);

    int getCol(int division, int offset, int sizeElement);

    bool checkClickedButtons(int x, int y);

    void loadButtons(FlagsUnitType type);

    void loadButtons(FlagsUnitType type, int tech);

    int loadRobotsButtons(int pos, int tech);

    int loadVehicleButtons(int pos, int tech);

    int loadVehiclesButtons(int pos, int tech);

    void cleanButtons();

    bool checkClickedButtons(int x, int y, Protocol protocol);

    int loadRobotsButtons(int pos, int unitCode, int tech);

    int loadVehiclesButtons(int pos, int unitCode, int tech);

    void loadButtons(FlagsUnitType type, int unitCode, int tech);
};


#endif //Z_PLAYERINTERFACE_H
