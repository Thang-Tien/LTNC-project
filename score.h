#ifndef scoreClass
#define scoreClass
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <fstream>
#include "LTexture.h"
class score:public LTexture
{
public:
    score();
    void loadBestScore (string path);
    void renderScore (SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
    void saveScore (string path);
    void loadTTFScore (SDL_Renderer* renderer);
    int currentSteps = 0, bestSteps = 0, currentTime = 0, bestTime = 0, startTime;

    TTF_Font* scoreFont;
    LTexture cStep, bStep, cTime, bTime;
};
#endif // scoreClass
