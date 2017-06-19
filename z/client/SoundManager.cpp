//
// Created by mbataglia on 19/06/17.
//

#include "SoundManager.h"

SoundManager::SoundManager(){
    Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048);
    sonidoMover = Mix_LoadWAV( "client/sounds/acknowledge_01.wav" );
}

void SoundManager::play(){
    Mix_PlayChannel( -1, sonidoMover, 0 );
}

SoundManager::~SoundManager() {
    Mix_FreeChunk(sonidoMover);
    Mix_CloseAudio();
}
