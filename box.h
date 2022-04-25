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
class box:public LTexture
{
public:
    box();
    LTexture boxTexture;
    int boxCount = 0;
    int XboxPosition [100];
    int YboxPosition [100];
    SDL_Rect boxRect[100];
    void loadBoxTexture (SDL_Renderer* renderer);
    void loadBoxData(const Map& gameMap);
    void renderBox (SDL_Renderer* renderer);

};

#endif // boxClass
