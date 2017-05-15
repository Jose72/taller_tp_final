#include "Animation.h"

Animation::Animation(SDL_Surface *screen,char *imagepath, int frame_w, int frame_h, int cant_frame) {
    this->screen = screen;

    SDL_Surface *loadedImage;
    loadedImage = SDL_LoadBMP(imagepath);
    this->image = SDL_DisplayFormat(loadedImage);
    SDL_FreeSurface(loadedImage);
    this->frame.w = frame_w;
    this->frame.h = frame_h;
    this->frame.x = 0;
    this->frame.y = 0;
    this->maxFrame = cant_frame;
    this->currentFrame = 0;

}

Animation::~Animation() {
    SDL_FreeSurface(this->image);
}

void Animation::animate(int posx, int posy) {
    SDL_Rect dest;
    dest.x = posx;
    dest.y = posy;
    //SDL_FillRect(screen,&frame,SDL_MapRGB(screen->format,0,0,0));
    SDL_BlitSurface(image,&frame,screen,&dest);
    this->currentFrame++;
    if(this->currentFrame >this->maxFrame){
        this->currentFrame = 0;
    }
    this ->frame.x = currentFrame *frame.w;
}
