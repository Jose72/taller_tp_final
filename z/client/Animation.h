#ifndef CLIENT_ANIMATION_H
#define CLIENT_ANIMATION_H

#include <SDL.h>
#include <string>

class Animation {
private:
    SDL_Surface *screen;
    SDL_Surface *image;
    SDL_Rect frame;


public:
   Animation(SDL_Surface *screen,std::string imagepath, int frame_w, int frame_h);

    ~Animation();
    void animate_static(int posx, int posy);
    void animate(int posx, int posy, SDL_Rect & cameraRect);
};


#endif //CLIENT_ANIMATION_H
