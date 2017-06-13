//
// Created by mbataglia on 23/05/17.
//

#ifndef Z_TTF_WRITTER_H
#define Z_TTF_WRITTER_H


#include <SDL_ttf.h>
#include <string>
class TTF_Writter {
private:
    TTF_Font* font;
    TTF_Font* giantFont;
public:
    TTF_Writter();

    void drawText(SDL_Surface *screen, std::string mensaje, Sint16 x, Sint16 y);

    virtual ~TTF_Writter();

    void drawGiantText(SDL_Surface *screen, std::string mensaje, Sint16 x, Sint16 y);
};


#endif //Z_TTF_WRITTER_H
