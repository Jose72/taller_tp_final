//
// Created by mbataglia on 19/06/17.
//
#define SECONDS_UNTIL_NEXT_ALARM 5
#define CREATE_ROBOT_SOUND 1000
#define CREATE_VEHICLE_SOUND 1001
#define WIN_FLAG_SOUND 1002
#define LOSS_FLAG_SOUND 1003
#define FORT_UNDER_ATTACK 1004
#define UNIT_UNDER_ATTACK 1005
#define TOUGHT_BULLET_EXPLOSION 1006

#include <iostream>
#include "SoundManager.h"
#include "Sound.h"
#include "../common/Lock.h"
#include "SpritesPool.h"
#include "ConstantsInterpretor.h"
#include <time.h>
#include <algorithm>



SoundManager::SoundManager(int idClient) {
    this->idClient = idClient;
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

    filePath = "comp_robot_manufactured.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[CREATE_ROBOT_SOUND] = sound;

    filePath = "comp_vehicle_manufactured.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[CREATE_VEHICLE_SOUND] = sound;

    filePath = "COMP10.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[WIN_FLAG_SOUND] = sound;

    filePath = "comp_territory_lost.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[LOSS_FLAG_SOUND] = sound;

    filePath = "comp_fort_under_attack.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[FORT_UNDER_ATTACK] = sound;

    filePath = "comp_youre_losing_05.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[UNIT_UNDER_ATTACK] = sound;

    filePath = "FLAMER.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[PYRO_BULLET] = sound;

    filePath = "TOUGHBULLET.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[TOUGHT_BULLET] = sound;

    filePath = "explosion_02.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[TOUGHT_BULLET_EXPLOSION] = sound;

    filePath = "LASERGUN.wav";
    sound = new Sound(soundPath + filePath,1);
    sounds[LASER_BULLET] = sound;


    lastDmgAlert = std::chrono::system_clock::now();
    lastSound = std::chrono::system_clock::now();
    pyroBulletSound = std::chrono::system_clock::now();


}

void SoundManager::playDamage(int unitOwner,int unitType,int preHeatlh,int postHealth){
    if(unitOwner == idClient){
        if(postHealth < preHeatlh){
            std::chrono::time_point<std::chrono::system_clock> newSound;
            newSound = std::chrono::system_clock::now();
            int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
                    (newSound-lastDmgAlert).count();
            if(elapsed_seconds >= SECONDS_UNTIL_NEXT_ALARM){
                if(unitType == FORT){
                    play(FORT_UNDER_ATTACK);
                } else {
                    play(UNIT_UNDER_ATTACK);
                }
                lastDmgAlert = std::chrono::system_clock::now();
            }

        }
    }
}

void SoundManager::playCreationUnit(int idOwner, int idUnit) {
    if(idClient == idOwner){
        ConstantsInterpretor constantsInterpretor;
        if(constantsInterpretor.isRobotUnit(idUnit)){
            play(CREATE_ROBOT_SOUND);
        } else {
            play(CREATE_VEHICLE_SOUND);
        }

    }
}

void SoundManager::playCaptureFlag(int idOwner, int previousOwner) {
    if(idClient == idOwner){
        play(WIN_FLAG_SOUND);
    }

    if(idClient == previousOwner){
        play(LOSS_FLAG_SOUND);
    }
}

void SoundManager::playGuns(int flag){
    tLock(this->mut);
    std::chrono::time_point<std::chrono::system_clock> newSound;
    newSound = std::chrono::system_clock::now();
    int elapsed_seconds = 0;
    if(flag == PYRO_BULLET){
        elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
                (newSound-pyroBulletSound).count();
        if(elapsed_seconds >= sounds[PYRO_BULLET]->getDuration()){
            sounds[PYRO_BULLET]->play();
            pyroBulletSound = std::chrono::system_clock::now();
        }
    } else {
        sounds[flag]->play();
    }
}

void SoundManager::play(int flag){
    ConstantsInterpretor constantsInterpretor;
    tLock(this->mut);
    int indexSound = flag;

    if(flag < CREATE_ROBOT_SOUND){
         indexSound = constantsInterpretor.getType((FlagsUnitType)flag);
    }
    std::chrono::time_point<std::chrono::system_clock> newSound;
    newSound = std::chrono::system_clock::now();
    int elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>
            (newSound-lastSound).count();
    if(elapsed_seconds >= sounds[indexSound]->getDuration()){
        sounds[indexSound]->play();
        lastSound = std::chrono::system_clock::now();
    }
}


void SoundManager::addToughBullet(int id) {
    if(std::find(toughBullets.begin(), toughBullets.end(), id) == toughBullets.end()) {
        toughBullets.push_back(id);
    }
}

void SoundManager::addLaserBullet(int id) {
    if(std::find(laserBullets.begin(), laserBullets.end(), id) == laserBullets.end()) {
        laserBullets.push_back(id);
    }
}

void SoundManager::playLaser(){
    int i = 0;
    bool newLaser = false;
    while(i < laserBullets.size() && !newLaser) {
        if(std::find(previousLaserBullets.begin(), previousLaserBullets.end(), laserBullets[i]) == previousLaserBullets.end()) {
            playGuns(LASER_BULLET);
            newLaser = true;
        }
        i++;
    }

    previousLaserBullets.clear();
    // std::copy(toughBullets.begin(), toughBullets.end(), previousToughBullets.begin());
    previousLaserBullets = laserBullets;
    laserBullets.clear();

}

void SoundManager::playToughBullets(){
    int i = 0;
    bool newBullet = false;
    bool explosion = false;
    while(i < toughBullets.size() && !newBullet) {
        if(std::find(previousToughBullets.begin(), previousToughBullets.end(), toughBullets[i]) == previousToughBullets.end()) {
            playGuns(TOUGHT_BULLET);
            newBullet = true;
        }
        i++;
    }

    i=0;
    while(i < previousToughBullets.size() && !explosion) {
        if(std::find(toughBullets.begin(), toughBullets.end(), previousToughBullets[i]) == toughBullets.end()) {
            playGuns(TOUGHT_BULLET_EXPLOSION);
            explosion = true;
        }
        i++;
    }
    previousToughBullets.clear();
   // std::copy(toughBullets.begin(), toughBullets.end(), previousToughBullets.begin());
    previousToughBullets = toughBullets;
    toughBullets.clear();
}


SoundManager::~SoundManager() {
    std::map <int, Sound*>::iterator it;
    for (it = sounds.begin(); it != sounds.end(); it++){
        delete it->second;
    }
    sounds.clear();
    Mix_CloseAudio();
}