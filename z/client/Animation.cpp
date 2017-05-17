#include "Animation.h"

Animation::Animation(SDL_Surface *screen,char *imagepath, int frame_w, int frame_h) {
    this->screen = screen;

    SDL_Surface *loadedImage;
    loadedImage = SDL_LoadBMP(imagepath);
    this->image = SDL_DisplayFormat(loadedImage);
    SDL_FreeSurface(loadedImage);
    this->frame.w = frame_w;
    this->frame.h = frame_h;
    this->frame.x = 0;
    this->frame.y = 0;
}

Animation::~Animation() {
    SDL_FreeSurface(this->image);
}

void Animation::animate(int posx, int posy) {
    SDL_Rect dest;
    dest.x = posx;
    dest.y = posy;
    SDL_BlitSurface(image,&frame,this->screen,&dest);
}
