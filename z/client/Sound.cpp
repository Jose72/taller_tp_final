//
// Created by mbataglia on 20/06/17.
//

#include "Sound.h"


Sound::Sound(std::string path, int duration){
    this->duration = duration;
    sound = Mix_LoadWAV(path.c_str());
}

void Sound::play(){
    Mix_PlayChannel( -1, sound, 0 );
}

int Sound::getDuration() const {
    return duration;
}

void Sound::setDuration(int duration) {
    Sound::duration = duration;
}

Sound::~Sound() {
    Mix_FreeChunk(sound);
}
