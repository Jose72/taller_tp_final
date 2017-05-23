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
public:
    TTF_Writter();

    void drawText(SDL_Surface *screen, std::string mensaje, int x, int y);

    virtual ~TTF_Writter();
};


#endif //Z_TTF_WRITTER_H
