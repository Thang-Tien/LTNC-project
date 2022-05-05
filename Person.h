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
class Person:public LTexture
{
public:
    Person();
    void handleEvent(int& direction, int& i, SDL_Event& e);
    void moveAndCheckCollision (SDL_Renderer* renderer, SDL_Rect& personRect, SDL_Rect boxRect[], int& boxCount, SDL_Rect wallRect[], int& wallCount);
    void renderPerson (SDL_Renderer* renderer, SDL_Rect& currentClip);
    int distance;
    void setVelX (int x);
    void setVelY (int y);
    bool goHorizontal, goVertical;
private:
    int velX, velY;
};


#endif // PersonClass
