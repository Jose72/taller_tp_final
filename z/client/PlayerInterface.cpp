//
// Created by mbataglia on 22/05/17.
//

#include <iostream>
#include <SDL_ttf.h>
#include "PlayerInterface.h"
#include "Animation.h"
#include "ClickableButtonGrunt.h"
#include "ClickableButtonLaser.h"
#include "ClickableButtonHeavyTank.h"
#include "ClickableButtonJeep.h"
#include "ClickableButtonCreateUnit.h"


#define PADDING 40
#define LEFT_PADDING 10
#define NO_WINNER -1

PlayerInterface::PlayerInterface(SDL_Surface* screen,
                                 int gameWidth,
                                 int gameHeight,
                                 int width){
    this->screen = screen;
    this->gameWidth = gameWidth;
    this->gameHeight = gameHeight;
    this->width = width;
    this->background = new Animation(this->screen,"client/sprites/tiles/5.bmp",32,32);
}

int PlayerInterface::getCol(int division,int offset,int sizeElement){
    return getCol(division,offset,sizeElement,0);
}

int PlayerInterface::getCol(int division,int offset,int sizeElement,int leftPadding){
    return gameWidth + (width/division) * offset - sizeElement + leftPadding;
}

bool PlayerInterface::checkClickedButtons(int x, int y,Protocol protocol){
    bool result = false;
    for(int i = 0; i != buttons.size(); i++) {
        result = result || buttons[i]->checkBounds(x, y, protocol);
    }
    return result;
}

std::string getUnitPortrait(FlagsUnitType type){
    std::string path;
    switch(type) {
        case BLUE_GRUNT:
            path = "client/sprites/portraits/grunt_blue.png";
            break;
        case GREEN_GRUNT:
            path = "client/sprites/portraits/grunt_green.png";
            break;
        case FORT_ALIVE:
            path = "client/sprites/portraits/fort.png";
            break;
        case FACTORY_ROBOTS_ALIVE:
            path = "client/sprites/portraits/factory_robots.png";
            break;
        case FACTORY_VEHICLES_ALIVE:
            path = "client/sprites/portraits/factory_vehicle.png";
            break;
        default:
            path = "client/sprites/portraits/grunt_red.png";
            break;
    }
    return path;
}

int PlayerInterface::loadRobotsButtons(int pos, int unitCode,int tech){
    //pos += PADDING para los saltos de linea
    if(tech >= 1){
        buttons.push_back(new ClickableButtonCreateUnit(getCol(3,1,100,LEFT_PADDING),pos,50,30,"Grunt",unitCode,GRUNT));
    }

    if(tech >= 2){
        buttons.push_back(new ClickableButtonCreateUnit(getCol(3,2,100,LEFT_PADDING),pos,50,30,"Psycho",unitCode,PSYCHO));
        pos += PADDING;
        buttons.push_back(new ClickableButtonCreateUnit(getCol(3,1,100,LEFT_PADDING),pos,50,30,"Tough",unitCode,TOUGHT));
    }

    if(tech >= 3){
        buttons.push_back(new ClickableButtonCreateUnit(getCol(3,2,100,LEFT_PADDING),pos,50,30,"Sniper",unitCode,SNIPER));
    }

    if(tech >= 4){
        pos += PADDING;
        buttons.push_back(new ClickableButtonCreateUnit(getCol(3,1,100,LEFT_PADDING),pos,50,30,"Pyro",unitCode,PYRO));
    }

    if(tech >= 5){
        buttons.push_back(new ClickableButtonCreateUnit(getCol(3,2,100,LEFT_PADDING),pos,50,30,"Laser",unitCode,LAZER));
    }

    pos += PADDING;
    return pos;
}

int PlayerInterface::loadVehiclesButtons(int pos,int unitCode, int tech){
    if(tech >= 1){
        buttons.push_back(new ClickableButtonCreateUnit(getCol(3,1,100,LEFT_PADDING),pos,50,30,"Jeep",unitCode,JEEP));
    }

    if(tech >= 2){
        buttons.push_back(new ClickableButtonCreateUnit(getCol(3,2,100,LEFT_PADDING),pos,50,30,"Light Tank",unitCode,LIGHT_TANK));
    }

    if(tech >= 3){
        pos += PADDING;
        buttons.push_back(new ClickableButtonCreateUnit(getCol(3,1,100,LEFT_PADDING),pos,50,30,"Medium Tank",unitCode,MEDIUM_TANK));
    }

    if(tech >= 4){
        buttons.push_back(new ClickableButtonCreateUnit(getCol(3,2,100,LEFT_PADDING),pos,50,30,"Heavy Tank",unitCode,HEAVY_TANK));
    }

    if(tech >= 5){
        pos += PADDING;
        buttons.push_back(new ClickableButtonCreateUnit(getCol(3,1,100,LEFT_PADDING),pos,50,30,"MML",unitCode,MML));
    }

    pos += PADDING;
    return pos;
}

void PlayerInterface::cleanButtons(){
    for(int i = 0; i != buttons.size(); i++) {
        delete(buttons[i]);
    }
    buttons.clear();
}

void PlayerInterface::loadButtons(FlagsUnitType type, int unitCode, int tech){
    int initialYPos = 300;
    switch (type){
        case FACTORY_ROBOTS_ALIVE:
            loadRobotsButtons(initialYPos,unitCode,tech);
            break;
        case FACTORY_VEHICLES_ALIVE:
            loadVehiclesButtons(initialYPos,unitCode,tech);
            break;
        case FORT_ALIVE:
            int newYpos = loadRobotsButtons(initialYPos,unitCode,tech);
            loadVehiclesButtons(newYpos,unitCode,tech);
            break;
    }

}

void PlayerInterface::show(SelectionHandler selectionHandler, TechLevelProtected &techProtected, WinnerProtected &winnerProtected,int idClient) {
    bool locked = SDL_MUSTLOCK(screen);
    if(locked)
        SDL_LockSurface(screen);
    cleanButtons();
    drawer.drawBackground(gameWidth,gameHeight,width,background);
    drawer.drawLine(screen,gameWidth);
    drawer.drawText(screen,"Z",getCol(2,1,0),0);
    drawer.drawText(screen,"Tech Lv:",getCol(3,1,0),20);
    drawer.drawText(screen,std::to_string(techProtected.getTechLevel()),getCol(3,2,0),20);
    if(selectionHandler.unit_select()){
        loadButtons(selectionHandler.getUnit()->get_type(),selectionHandler.getUnit()->get_unit_code(),techProtected.getTechLevel());
        drawer.drawImage(screen,getUnitPortrait(selectionHandler.getUnit()->get_type()).c_str(), getCol(2,1,32), 50);
        drawer.drawText(screen,"Pos X: ",getCol(3,1,0),150);
        drawer.drawText(screen,std::to_string(selectionHandler.getUnit()->get_posx()),getCol(3,2,0),150);
        drawer.drawText(screen,"Pos Y: ",getCol(3,1,0),170);
        drawer.drawText(screen,std::to_string(selectionHandler.getUnit()->get_posy()),getCol(3,2,0),170);
        drawer.drawText(screen,"Vida: ",getCol(3,1,0),190);
        drawer.drawText(screen,std::to_string(selectionHandler.getUnit()->get_heatlh()),getCol(3,2,0),190);
        drawer.drawText(screen,"Tipo: ",getCol(3,1,0),210);
        drawer.drawText(screen,std::to_string(selectionHandler.getUnit()->get_type()),getCol(3,2,0),210);
    } else {
        drawer.drawText(screen,"Nada seleccionado",getCol(2,1,0),150);
    }

    for(int i = 0; i != buttons.size(); i++) {
        drawer.drawButton(screen,buttons[i]);
    }

    if(winnerProtected.getWinner() != NO_WINNER){
        if(winnerProtected.getWinner() == idClient){
            drawer.drawGiantText(screen,"VICTORY",100,400);
        } else {
            drawer.drawGiantText(screen,"DEFEAT",100,400);
        }
    }

    if(locked)
        SDL_UnlockSurface(screen);
}

PlayerInterface::~PlayerInterface() {
    cleanButtons();
    delete(background);
}

