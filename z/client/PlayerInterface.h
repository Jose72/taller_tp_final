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

    void show(SelectionHandler selectionHandler, TechLevelProtected &techProtected, WinnerProtected &winnerProtected,int idClient);

    virtual ~PlayerInterface();

    int getCol(int division, int offset, int sizeElement, int leftPadding);

    void loadButtons(Unit * unit);

    void cleanButtons();

    bool checkClickedButtons(int x, int y, Protocol protocol);

    int loadRobotsButtons(int pos, int unitCode, int tech);

    int loadVehiclesButtons(int pos, int unitCode, int tech);

    int getCol(int division, int offset, int sizeElement);

    void drawTech(int tech);

    void drawCompletionTime(int time);
};


#endif //Z_PLAYERINTERFACE_H
