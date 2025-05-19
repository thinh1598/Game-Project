#ifndef SOUND
#define SOUND

#include <bits/stdc++.h>
#include <SDL_mixer.h>
#include "graphics.h"
#include "Input_Valuable.h"

using namespace std;

Mix_Music *music;
Mix_Music *music_game;
Mix_Music *zombie_sound;
Mix_Chunk *Fight[3];
Mix_Chunk *Lose;
Mix_Chunk *ZombieDead;
Mix_Chunk *HumanHeart;
Mix_Chunk *LevelUp;
Mix_Chunk *Upgrade;

void initSound()
{
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    music = loadMusic("Sound/Sound.mp3");
    music_game = loadMusic("Sound/music.mp3");
    zombie_sound = loadMusic("Sound/Zombie.mp3");
    Fight[0] = loadSound("Sound/Fight1.mp3");
    Fight[1] = loadSound("Sound/Fight2.mp3");
    Fight[2] = loadSound("Sound/Fight3.mp3");
    Lose = loadSound("Sound/Lose.mp3");
    Upgrade = loadSound("Sound/Upgrade.mp3");
    ZombieDead = loadSound("Sound/ZombieDead.mp3");
    HumanHeart = loadSound("Sound/Heart.mp3");
    LevelUp = loadSound("Sound/LevelUp.mp3");
}

void Music_BackGround()
{
    playMusic(music);
}

void End_Music_BackGround()
{
    Mix_FreeMusic(music);
}

void Music_Game()
{
    playMusic(music_game);
}

void End_Music_Game()
{
    Mix_FreeMusic(music_game);
}

void Zombie_Music()
{
    playMusic(zombie_sound);
}

void End_Zombie_Music()
{
    Mix_FreeMusic(zombie_sound);
}

void Lose_Sound()
{
    playSound(Lose);
}

void Level_Up()
{
    playSound(LevelUp);
}

void Fight_Sound()
{
    srand(time(0));
    int x = rand() % 3;
    playSound(Fight[x]);
}

void Zombie_Dead_Sound()
{
    playSound(ZombieDead);
}

void Human_Heart()
{
    playSound(HumanHeart);
}

void Update()
{
    playSound(Upgrade);
}

#endif // SOUND
