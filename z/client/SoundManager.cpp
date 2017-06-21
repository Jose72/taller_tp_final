//
// Created by mbataglia on 19/06/17.
//

#include <iostream>
#include "SoundManager.h"
#include "Sound.h"
#include "../common/Lock.h"
#include "SpritesPool.h"
#include "ColorToType.h"
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <caca_conio.h>
#define SOUND_PATH "client/sounds/"

SoundManager::SoundManager(){
    std::string soundPath;
    soundPath = "client/sounds/";
    std::string filePath;

    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Sound* sound;

    filePath = "selected_grunt.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[GRUNT] = sound;

    filePath = "acknowledge_00.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[JEEP] = sound;

    filePath = "acknowledge_01.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[MEDIUM_TANK] = sound;

    filePath = "acknowledge_02.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[LIGHT_TANK] = sound;

    filePath = "acknowledge_03.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[HEAVY_TANK] = sound;

    filePath = "acknowledge_04.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[MML] = sound;

    filePath = "selected_psycho.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[PSYCHO] = sound;

    filePath = "selected_tough.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[TOUGHT] = sound;

    filePath = "selected_pyro.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[PYRO] = sound;

    filePath = "selected_sniper.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[SNIPER] = sound;

    filePath = "selected_laser.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[LAZER] = sound;

    filePath = "CONNECTL.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[FORT] = sound;

    filePath = "ROBFACT5.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[ROBOT_FACTORY] = sound;

    filePath = "TRUCKROL.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[VEHICLE_FACTORY] = sound;

    lastSound = std::chrono::system_clock::now();

}

void SoundManager::play(int flag){
    ColorToType colorToType;
    tLock(this->mut);
    int indexSound = colorToType.getType((FlagsUnitType)flag);
    std::cout << indexSound << std::endl;
    std::chrono::time_point<std::chrono::system_clock> newSound;
    newSound = std::chrono::system_clock::now();
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
            (newSound-lastSound).count();
    if(elapsed_seconds >= sounds[indexSound]->getDuration()){
        sounds[indexSound]->play();
        lastSound = std::chrono::system_clock::now();
    }
}

SoundManager::~SoundManager() {
    std::map <int, Sound*>::iterator it;
    for (it = sounds.begin(); it != sounds.end(); it++){
        delete it->second;
    }
    sounds.clear();
    Mix_CloseAudio();
}
