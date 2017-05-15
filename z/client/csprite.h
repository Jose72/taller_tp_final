#ifndef CLIENT_CSPRITE_H
#define CLIENT_CSPRITE_H

#include <SDL_video.h>

#define TRUE 1
#define FALSE 0

//CFrame representa un frame independiente de un sprite
class CFrame {
public:
    SDL_Surface *img;
    void load(char *path);
    void unload();
};


//La clase CSprite esta formada por un array de frames
class CSprite{
private:
    int posx, posy;
    int estado;
    int nframes;
    int cont;

public:
    CFrame *sprite;
    CSprite(int nf);
    CSprite();
    void finalize();
    void addframe(CFrame frame);
    void selframe(int nf);
    int frames();
    void setx(int x);
    void sety(int y);
    void addx(int c);
    void addy(int c);
    int getx();
    int gety();
    int getw();
    int geth();
    void draw(SDL_Surface *superficie);
    int colision(CSprite sp);
};

#endif //CLIENT_CSPRITE_H
