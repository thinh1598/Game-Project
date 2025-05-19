#ifndef TEXT
#define TEXT

#include<bits/stdc++.h>
#include <SDL_ttf.h>
#include "Input_Valuable.h"
#include "graphics.h"

using namespace std;

TTF_Font *text;
SDL_Texture *Txt;

TTF_Font* loadFont(const char* path, int Size)
{
    TTF_Font* gFont = TTF_OpenFont( path, Size );
    if (gFont == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load font %s", TTF_GetError());
    }
}

SDL_Texture* renderText(const char *text, TTF_Font* font, SDL_Color textColor)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, text, textColor );
    if( textSurface == nullptr ) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Render text surface %s", TTF_GetError());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, textSurface );
    if( texture == nullptr ) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create texture from text %s", SDL_GetError());
    }

    SDL_FreeSurface( textSurface );
    return texture;
}

void initText()
{
    if (TTF_Init() == -1)
    {
        logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ", TTF_GetError());
    }
}

void RenderText(SDL_Texture *texture, int x, int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void renText(const char *s, int sz, int w, int h, int r, int g, int b)
{
    SDL_Color color = { r, g, b };
    text = loadFont("Font.otf", sz);
    Txt = renderText(s, text, color);
    RenderText(Txt, w, h);
}

#endif // TEXT
