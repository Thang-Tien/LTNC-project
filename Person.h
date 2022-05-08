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
#include "box.h"
#include "score.h"
class Person:public LTexture
{
public:
    Person();
    void handleEvent(int& direction, int& i, SDL_Event& e);
    void moveAndCheckCollision (SDL_Renderer* renderer, SDL_Rect& personRect, SDL_Rect boxRect[], int& boxCount, SDL_Rect wallRect[], int& wallCount);
    void renderPerson (SDL_Renderer* renderer, SDL_Rect& currentClip);
    void setVelX (int x);
    void setVelY (int y);
    bool goHorizontal, goVertical;

    int distance, lastPosX, lastPosY;
private:
    int velX, velY;
};


#endif // PersonClass
