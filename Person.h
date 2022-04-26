#ifndef PersonClass
#define PersonClass
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "LTexture.h"
class Person:public LTexture
{
public:
    Person();
    void handleEvent(int& direction, int& i, SDL_Event& e);
    void move(SDL_Rect& personRect, SDL_Rect boxRect[], int& boxCount);
    void renderPerson (SDL_Renderer* renderer, SDL_Rect& currentClip);
    int distance;
    void setVelX (int x);
    void setVelY (int y);

private:
    int velX, velY;
};


#endif // PersonClass
