#ifndef mapClass
#define mapClass
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <fstream>
#include "LTexture.h"
class Map:public LTexture
{
public:
    Map();
    LTexture mapTexture[24][14];
    string mapDataPreLoad[14];
    char mapData[24][14];
    SDL_Rect mapRect[24][14];
    void loadMapData (SDL_Renderer* renderer, string path);
    void renderMap (SDL_Renderer* renderer);
    int XpersonPosition;
    int YpersonPosition;

    int boxCount = 0;
    int wallCount = 0;
    int XwallPosition [100];
    int YwallPosition [100];
    int XboxPosition [100];
    int YboxPosition [100];

};

#endif // mapClass
