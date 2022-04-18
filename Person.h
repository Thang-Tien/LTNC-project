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
    const int Person_Vel = 10;

    Person();
    void handleEvent(int& direction, int& i, SDL_Event& e);
    void move(SDL_Rect& personRect, SDL_Rect& boxRect);
    void renderPerson (SDL_Renderer* renderer, SDL_Rect& currentClip);
    bool checkCollision(SDL_Rect a, SDL_Rect b);

private:
    int velX, velY;
};


#endif // PersonClass
