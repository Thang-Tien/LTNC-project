#ifndef smallMapClass
#define smallMapClass
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <fstream>
#include "LTexture.h"
class smallMap:public LTexture
{
public:

    smallMap();
    LTexture smallMapTexture[17][16];
    LTexture floor, grass, wall, goal, box, boxOnGoal, person;
    string smallMapDataPreLoad[16];

    char smallMapData[17][16];
    SDL_Rect smallMapRect[17][16];

    void loadsmallMapData (SDL_Renderer* renderer, string path);
    void resetsmallMapData ();
    void rendersmallMap (SDL_Renderer* renderer);

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
#endif // smallsmallMapClass
