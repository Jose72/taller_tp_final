#ifndef CLIENT_ANIMATION_H
#define CLIENT_ANIMATION_H

#include <SDL.h>

class Animation {
private:
    SDL_Surface *screen;
    SDL_Surface *image;
    int currentFrame;
    int maxFrame;
    SDL_Rect frame;

public:
    //crea la animacion con el path del archivo y la anchura y el alto del frame
    //SI en cantidad de frames se pone 0 es un sprite comun
    Animation(SDL_Surface *screen,char *imagepath, int frame_w, int frame_h, int cant_frame);

    ~Animation();
    void animate(int posx, int posy);
};


#endif //CLIENT_ANIMATION_H
