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
    LTexture mapTexture[17][16];
    LTexture floor, grass, goal;
    string mapDataPreLoad[16];

    char mapData[17][16];
    SDL_Rect mapRect[17][16];

    void loadMapData (SDL_Renderer* renderer, string path);
    void resetMapData ();
    void renderMap (SDL_Renderer* renderer);

    int XpersonPosition;
    int YpersonPosition;

    int wallCount = 0;
    int XwallPosition [100];
    int YwallPosition [100];

    int boxCount = 0;
    int XboxPosition [100];
    int YboxPosition [100];

    int goalCount = 0;
    int XgoalPosition [100];
    int YgoalPosition [100];

};

#endif // mapClass
