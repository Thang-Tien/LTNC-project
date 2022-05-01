#ifndef boxClass
#define boxClass
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "LTexture.h"
#include "Map.h"
#include <algorithm>
class box:public LTexture
{
public:
    box();
    LTexture boxTexture;
    LTexture boxWinTexture;

    int boxCount = 0;
    SDL_Rect boxRect[50];
    void clearBoxData ();

    int goalCount = 0;
    SDL_Rect goalRect [50];
    bool scoredGoals [50];
    void clearGoalData ();

    bool winCheck ();
    void loadBoxTexture (SDL_Renderer* renderer);
    void loadBoxData(const Map& gameMap);
    void renderBox (SDL_Renderer* renderer);
    void sortBox();

};

#endif // boxClass
