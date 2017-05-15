#ifndef CLIENT_ANIMATION_H
#define CLIENT_ANIMATION_H

#include <SDL.h>

class Animation {
private:
    SDL_Surface *screen;
    SDL_Surface *image;
    SDL_Rect frame;

public:
   Animation(SDL_Surface *screen,char *imagepath, int frame_w, int frame_h);

    ~Animation();
    void animate(int posx, int posy);
};


#endif //CLIENT_ANIMATION_H
