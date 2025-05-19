#ifndef CHARACTER
#define CHARACTER

#include<bits/stdc++.h>
#include<SDL.h>
#include <SDL_image.h>
#include "graphics.h"
#include "Input_Valuable.h"
#include "Text.h"

using namespace std;

SDL_Texture* marco_walk[18];
SDL_Texture* marco_jump[18];
SDL_Texture* marco_atk[2][18];
SDL_Texture* marco_dead[18];
struct Character {
    int x = SCREEN_WIDTH / 2;
    int y = 650;
    int speed = 10;
    int direction = 1;
    int act_walk = 0;
    float act_jump = 1;
    int act_attack = 0;
    int act_dead = 0;
    int type_attack = 1;

    int getDirection()
    {
        return direction;
    }

    pair<int, int> getlocation()
    {
        return make_pair(x, y);
    }

    void input(SDL_Renderer *renderer)
    {
        marco_walk[0] = loadTexture("Animation/walk/Walk1.png", renderer);
        marco_walk[1] = loadTexture("Animation/walk/Walk2.png", renderer);
        marco_walk[2] = loadTexture("Animation/walk/Walk3.png", renderer);
        marco_walk[3] = loadTexture("Animation/walk/Walk4.png", renderer);
        marco_walk[4] = loadTexture("Animation/walk/Walk5.png", renderer);
        marco_walk[5] = loadTexture("Animation/walk/Walk6.png", renderer);
        marco_walk[6] = loadTexture("Animation/walk/Walk7.png", renderer);
        marco_walk[7] = loadTexture("Animation/walk/Walk8.png", renderer);

        marco_jump[1] = loadTexture("Animation/jump/jump1.png", renderer);
        marco_jump[2] = loadTexture("Animation/jump/jump2.png", renderer);
        marco_jump[3] = loadTexture("Animation/jump/jump3.png", renderer);
        marco_jump[4] = loadTexture("Animation/jump/jump4.png", renderer);
        marco_jump[5] = loadTexture("Animation/jump/jump5.png", renderer);
        marco_jump[6] = loadTexture("Animation/Jump/jump6.png", renderer);
        marco_jump[7] = loadTexture("Animation/jump/jump7.png", renderer);

        marco_atk[0][0] = loadTexture("Animation/atk1/1.png", renderer);
        marco_atk[0][1] = loadTexture("Animation/atk1/2.png", renderer);
        marco_atk[0][2] = loadTexture("Animation/atk1/3.png", renderer);
        marco_atk[0][3] = loadTexture("Animation/atk1/4.png", renderer);

        marco_atk[1][0] = loadTexture("Animation/atk2/1.png", renderer);
        marco_atk[1][1] = loadTexture("Animation/atk2/2.png", renderer);
        marco_atk[1][2] = loadTexture("Animation/atk2/3.png", renderer);
        marco_atk[1][3] = loadTexture("Animation/atk2/4.png", renderer);

        marco_dead[0] = loadTexture("Animation/dead/Dead1.png", renderer);
        marco_dead[1] = loadTexture("Animation/dead/Dead2.png", renderer);
        marco_dead[2] = loadTexture("Animation/dead/Dead3.png", renderer);
    }

    void RenderCharacter(SDL_Renderer *renderer, bool &jumpping, bool &attacking)
    {
        SDL_Texture *texture;

        if(End == 1) texture = marco_dead[act_dead];
        else if(jumpping) texture = marco_jump[int(act_jump)];
        else if(attacking) texture = marco_atk[type_attack][act_attack];
        else texture = marco_walk[act_walk];

        SDL_Rect dest;

        dest.x = x;
        dest.y = y;

        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        SDL_Point center;
        center.x = 0;
        center.y = 0;

        if (direction == 1)
            SDL_RenderCopyEx(renderer, texture, 0, &dest, 0, &center, SDL_FLIP_NONE);
        else
            SDL_RenderCopyEx(renderer, texture, 0, &dest, 0, &center, SDL_FLIP_HORIZONTAL);
    }

    void nothing()
    {
        act_walk = 0;
    }

    void left()
    {
        direction = -1;
        act_walk++;
        if (act_walk == 8)
            act_walk = 0;
        x -= speed;
    }

    void right()
    {
        direction = 1;
        act_walk++;
        if (act_walk == 8)
            act_walk = 0;
        x += speed;
    }

    void up()
    {
        if(act_jump <= 4) y -= speed;
        if(act_jump >= 6) y += 2 * speed;
    }

    void dead()
    {
        act_dead++;
        if(act_dead > 2) act_dead = 2;
    }

    void action(SDL_Event &e)
    {
        if (e.key.keysym.sym == SDLK_a)
        {
            left();
            old = Time;
        }

        if (e.key.keysym.sym == SDLK_d)
        {
            right();
            old = Time;
        }
        if (e.key.keysym.sym == SDLK_w)
        {
            jumpping = 1;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            attacking = 1;
        }

        if(jumpping == 1)
        {
            if(act_jump >= 8)
            {
                y = 650;
                act_jump = 1;
                jumpping = 0;
                x += direction * 25;
            }
            else
            {
                up();
                if(direction == -1) left();
                else right();
                act_jump += 0.5;
            }
        }

        if(attacking == 1)
        {
            type_attack = 1 - type_attack;
            if(act_attack >= 4)
            {
                act_attack = 0;
                attacking = 0;
                SDL_Delay(20);
            }
            else
            {
                act_attack++;
            }
        }
    }

    void quit()
    {
        for (int i = 0; i < 8; i++)
        {
            SDL_DestroyTexture(marco_walk[i]);
            marco_walk[i] = NULL;
        }

        for (int i = 1; i <= 9; i++)
        {
            SDL_DestroyTexture(marco_jump[i]);
            marco_jump[i] = NULL;
        }

        for(int i = 0; i <= 1; i++)
            for(int j = 0; j < 5; j++){
                SDL_DestroyTexture(marco_atk[i][j]);
                marco_atk[i][j] = NULL;
            }
    }
} character;

struct Health
{
    int y = 725;
    int x;
    int appear = 0;
    int color = 0;

    void More(int tmp)
    {
        x = tmp;
        appear = 1;
    }

    void action()
    {
        if(appear == 0) return;
        renText("o", 15, x, y, 225, color, color);
        color = 225 - color;
        if((character.x >= x - 70) && (character.x <= x - 45))
        {
            appear = 0;
            Heart++;
//            Update();
        }
    }
} health;
#endif
