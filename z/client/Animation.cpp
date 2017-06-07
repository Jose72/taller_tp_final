#include "Animation.h"

Animation::Animation(SDL_Surface *screen,std::string imagepath, int frame_w, int frame_h) {
    this->screen = screen;

    SDL_Surface *loadedImage;
    const char * imagepath2 = imagepath.c_str();
    loadedImage = SDL_LoadBMP(imagepath2);
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

void Animation::animate(int posx, int posy, SDL_Rect &cameraRect) {
    SDL_Rect position;
    position.x = posx;
    position.y = posy;
    SDL_Rect animationReact = {position.x - cameraRect.x,position.y - cameraRect.y, this->frame.w, this->frame.h};
    SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 0, 0, 0));
    SDL_BlitSurface(image,&frame,this->screen,&animationReact);
}

void Animation::animate_static(int posx, int posy){
    SDL_Rect position;
    position.x = posx;
    position.y = posy;
    SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 0, 0, 0));
    SDL_BlitSurface(image,&frame,this->screen,&position);
}
