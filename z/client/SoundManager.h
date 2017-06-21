//
// Created by mbataglia on 19/06/17.
//

#ifndef Z_SOUNDMANAGER_H
#define Z_SOUNDMANAGER_H


#include <SDL_mixer.h>
#include <ctime>
#include <chrono>
#include <mutex>
#include "Sound.h"
#include "SpritesPool.h"
#include "../common/constants.h"

class SoundManager {
private:
    std::mutex mut;
    std::chrono::time_point<std::chrono::system_clock> lastSound;
    std::map<int,Sound*> sounds;
public:
    SoundManager();
    ~SoundManager();


    void play();

    void play(FlagsUnitType flag);

    void play(int flag);
};



#endif //Z_SOUNDMANAGER_H
