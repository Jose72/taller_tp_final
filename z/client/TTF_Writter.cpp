//
// Created by mbataglia on 23/05/17.
//

#include <iostream>
#include "TTF_Writter.h"

TTF_Writter::TTF_Writter() {
    font=TTF_OpenFont("client/fonts/roboto/Roboto-Medium.ttf", 16);
    if(!font) {
        std::cout << "TTF_OpenFont: " << TTF_GetError() << std::endl;
    }
}

TTF_Writter::~TTF_Writter() {
    //TTF_CloseFont(font);
    font=NULL;
}

void TTF_Writter::drawText(SDL_Surface* screen,std::string mensaje,int x,int y) {
    SDL_Color color={255,255,255};
    SDL_Surface *text_surface;
    if(!(text_surface=TTF_RenderText_Blended(font,mensaje.c_str(),color))) {
        std::cout << "TTF_OpenFont: " << TTF_GetError() << std::endl;
    } else {
        SDL_Rect rcDest = { x, y, 0, 0 };
        SDL_BlitSurface(text_surface,NULL,screen,&rcDest);
        SDL_FreeSurface(text_surface);
    }
}