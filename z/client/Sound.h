//
// Created by mbataglia on 20/06/17.
//

#ifndef Z_SOUND_H
#define Z_SOUND_H

#include <string>
#include <SDL_mixer.h>

class Sound {
private:


    int duration;
    Mix_Chunk *sound;
public:
    ~Sound();
    Sound(std::string path, int duration);
    void play();

    int getDuration() const;

    void setDuration(int duration);
};


#endif //Z_SOUND_H
