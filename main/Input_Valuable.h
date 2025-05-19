#ifndef VALUABLE
#define VALUABLE

#include <SDL.h>


const char *WINDOW_TITLE = "METAL SLUG: MEMORIES";
SDL_Window *window = initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
SDL_Renderer *renderer = createRenderer(window);

SDL_Texture *BG;
SDL_Texture *NameGame;
SDL_Texture *KeyPressToPlay;
SDL_Texture *Score;
SDL_Texture *TheEnd;

long long Time = 0;
long long old = 0;
long long Time2 = 0;
bool jumpping = 0;
bool attacking = 0;
int End = 0;
int oldlevel = 0;
int oldHeart = 0;
int level = 100;
int Level = 1;
int Heart = 3;

int score = 0;
int highscore = 0;

bool muted = false;

Uint32 startTime = 0;
#endif // VALUABLE
