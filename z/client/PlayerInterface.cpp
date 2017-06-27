//
// Created by mbataglia on 22/05/17.
//

#include <iostream>
#include <SDL_ttf.h>
#include "PlayerInterface.h"
#include "Animation.h"
#include "ClickableButtonCreateUnit.h"
#include "ConstantsInterpretor.h"


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

std::string PlayerInterface::getUnitPortrait(FlagsUnitType type){
    std::string path;
    switch(type) {
        case FACTORY_ROBOTS_ALIVE:
            path = "client/sprites/portraits/factory_robots.png";
            break;
        case FACTORY_VEHICLES_ALIVE:
            path = "client/sprites/portraits/factory_vehicle.png";
            break;       ;
        case FORT_ALIVE:
            path = "client/sprites/portraits/fort.png";
            break;
        default:
            int color = constantsInterpretor.getColor(type);
            switch (color){
                case TEAM_BLUE:
                    path = "client/sprites/portraits/grunt_blue.png";
                    break;
                case TEAM_GREEN:
                    path = "client/sprites/portraits/grunt_green.png";
                    break;
                case TEAM_YELLOW:
                    path = "client/sprites/portraits/grunt_yellow.png";
                    break;
                case TEAM_RED:
                    path = "client/sprites/portraits/grunt_red.png";
                    break;
                case NO_COLOR:
                    path = "client/sprites/portraits/nocolor.png";
                    break;
                default:
                    path = "client/sprites/portraits/nocolor.png";
                    break;
            }
            break;
    }
    return path;
}

int PlayerInterface::loadRobotsButtons(int pos, int unitCode,int tech){
    //pos += PADDING para los saltos de linea
    if(tech >= 1){
        buttons.push_back(new ClickableButtonCreateUnit(getCol(3,1,100,LEFT_PADDING),
                                                        pos,50,30,"Grunt",unitCode,GRUNT,factoriesCreating));
    }

    if(tech >= 2){
        buttons.push_back(new ClickableButtonCreateUnit(getCol(3,2,100,LEFT_PADDING),
                                                        pos,50,30,"Psycho",unitCode,PSYCHO,factoriesCreating));
        pos += PADDING;
        buttons.push_back(new ClickableButtonCreateUnit(getCol(3,1,100,LEFT_PADDING),
                                                        pos,50,30,"Tough",unitCode,TOUGHT,factoriesCreating));
    }

    if(tech >= 3){
        buttons.push_back(new ClickableButtonCreateUnit(getCol(3,2,100,LEFT_PADDING),
                                                        pos,50,30,"Sniper",unitCode,SNIPER,factoriesCreating));
    }

    if(tech >= 4){
        pos += PADDING;
        buttons.push_back(new ClickableButtonCreateUnit(getCol(3,1,100,LEFT_PADDING),
                                                        pos,50,30,"Pyro",unitCode,PYRO,factoriesCreating));
    }

    if(tech >= 5){
        buttons.push_back(new ClickableButtonCreateUnit(getCol(3,2,100,LEFT_PADDING),
                                                        pos,50,30,"Laser",unitCode,LAZER,factoriesCreating));
    }

    pos += PADDING;
    return pos;
}

int PlayerInterface::loadVehiclesButtons(int pos,int unitCode, int tech){
    if(tech >= 1){
        buttons.push_back(new ClickableButtonCreateUnit(getCol(3,1,100,LEFT_PADDING),
                                                        pos,50,30,"Jeep",unitCode,JEEP,factoriesCreating));
    }

    if(tech >= 2){
        buttons.push_back(new ClickableButtonCreateUnit(getCol(3,2,100,LEFT_PADDING),
                                                        pos,50,30,"Light Tank",unitCode,LIGHT_TANK,factoriesCreating));
    }

    if(tech >= 3){
        pos += PADDING;
        buttons.push_back(new ClickableButtonCreateUnit(getCol(3,1,100,LEFT_PADDING),
                                                        pos,50,30,"Medium Tank",unitCode,MEDIUM_TANK,factoriesCreating));
    }

    if(tech >= 4){
        buttons.push_back(new ClickableButtonCreateUnit(getCol(3,2,100,LEFT_PADDING),
                                                        pos,50,30,"Heavy Tank",unitCode,HEAVY_TANK,factoriesCreating));
    }

    if(tech >= 5){
        pos += PADDING;
        buttons.push_back(new ClickableButtonCreateUnit(getCol(3,1,100,LEFT_PADDING),
                                                        pos,50,30,"MML",unitCode,MML,factoriesCreating));
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

void PlayerInterface::drawTech(int tech){
    drawer.drawText(screen,"Tech Lv:",getCol(3,1,0),0);
    drawer.drawText(screen,std::to_string(tech),getCol(3,2,0),0);
}

void PlayerInterface::drawCompletionTime(int time, int idUnit) {
    drawer.drawText(screen,"Unit Creation:",getCol(3,1,0),20);
    drawer.drawText(screen,std::to_string(100 - time) + "%",getCol(3,2,0),20);
    if ( factoriesCreating.find(idUnit) != factoriesCreating.end() ) {
        drawer.drawText(screen,
                        constantsInterpretor.idToString(factoriesCreating[idUnit]),
                        getCol(3,2,0),
                        40);
    }

}

void PlayerInterface::loadButtons(Unit *unit) {
    int initialYPos = 300;
    switch (unit->get_type()){
        case FACTORY_ROBOTS_ALIVE:
            loadRobotsButtons(initialYPos,unit->get_unit_code(),unit->get_techLevel());
            drawTech(unit->get_techLevel());
            drawCompletionTime(unit->getCompletionTime(), unit->get_unit_code());
            break;
        case FACTORY_VEHICLES_ALIVE:
            loadVehiclesButtons(initialYPos,unit->get_unit_code(),unit->get_techLevel());
            drawTech(unit->get_techLevel());
            drawCompletionTime(unit->getCompletionTime(), unit->get_unit_code());
            break;
        case FORT_ALIVE:
            int newYpos = loadRobotsButtons(initialYPos,unit->get_unit_code(),unit->get_techLevel());
            loadVehiclesButtons(newYpos,unit->get_unit_code(),unit->get_techLevel());
            drawTech(unit->get_techLevel());
            drawCompletionTime(unit->getCompletionTime(), unit->get_unit_code());
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
    if(selectionHandler.unit_select()){
        loadButtons(selectionHandler.getUnit());
        drawer.drawImage(screen,getUnitPortrait(selectionHandler.getUnit()->get_type()).c_str(), getCol(2,1,32), 70);
        drawer.drawText(screen,"Pos X: ",getCol(3,1,0),160);
        drawer.drawText(screen,std::to_string(selectionHandler.getUnit()->get_posx()),getCol(3,2,0),160);
        drawer.drawText(screen,"Pos Y: ",getCol(3,1,0),180);
        drawer.drawText(screen,std::to_string(selectionHandler.getUnit()->get_posy()),getCol(3,2,0),180);
        drawer.drawText(screen,"Vida: ",getCol(3,1,0),200);
        drawer.drawText(screen,std::to_string(selectionHandler.getUnit()->get_heatlh()),getCol(3,2,0),200);
        drawer.drawText(screen,"Tipo: ",getCol(3,1,0),220);
        drawer.drawText(screen,std::to_string(selectionHandler.getUnit()->get_type()),getCol(3,2,0),220);
        if(selectionHandler.getUnit()->getTypeDriver() > -1){
            drawer.drawText(screen,"Conductor: ",getCol(3,1,0),240);
            drawer.drawText(screen,
                            constantsInterpretor.idToString(selectionHandler.getUnit()->getTypeDriver()),
                            getCol(3,2,0),
                            240);
        }
    } else {
        drawer.drawText(screen,"Nada seleccionado",getCol(2,1,0),160);
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

