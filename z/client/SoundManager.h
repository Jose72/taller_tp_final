//
// Created by mbataglia on 19/06/17.
//

#ifndef Z_SOUNDMANAGER_H
#define Z_SOUNDMANAGER_H


#include <SDL_mixer.h>

class SoundManager {
private:
    Mix_Chunk *sonidoMover;
public:
    SoundManager();
    ~SoundManager();


    void play();
};



#endif //Z_SOUNDMANAGER_H
