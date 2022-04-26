#ifndef wallClass
#define wallClass
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <fstream>
#include "LTexture.h"
#include "Map.h"
class wall:public LTexture
{
public:
    LTexture wallTexture;
    int wallCount = 0;
    int XwallPosition [100];
    int YwallPosition [100];
    SDL_Rect wallRect [100];
    void loadWallData (const Map& gameMap);
    void loadWallTexture (SDL_Renderer* renderer);
    void renderWall (SDL_Renderer* renderer);
};

#endif // wallClass
