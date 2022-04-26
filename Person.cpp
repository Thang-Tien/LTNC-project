#include "Person.h"
Person::Person()
{
    LTexture();

    velX = 0;
    velY = 0;
    distance = 0;
}

void Person::handleEvent (int& direction, int& left, SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
        {
            velY -= 1;
            direction = 3;
            break;

        }
        case SDLK_DOWN:
        {
            velY += 1;
            direction = 0;
            break;

        }
        case SDLK_LEFT:
        {
            velX -= 1;
            direction = 1;
            break;

        }
        case SDLK_RIGHT:
        {

            velX += 1;
            direction = 2;
            break;
        }
        }
    }

}

void Person::move(SDL_Rect& personRect, SDL_Rect boxRect[], int& boxCount)
{
    posX += velX;
    posY += velY;

    personRect = {posX, posY, personRect.w, personRect.h};
    for (int i = 0; i < boxCount; i++)
    {
        if (velX > 0)
        {
            if (checkCollision(personRect, boxRect[i]) == true)
            {
                boxRect[i].x = posX + personRect.w;
                boxRect[i] = {boxRect[i].x, boxRect[i].y, boxRect[i].w, boxRect[i].h};
            }
        }
        if (velX < 0)
        {
            if (checkCollision(personRect, boxRect[i]) == true)
            {
                boxRect[i].x = posX - boxRect[i].w;
                boxRect[i] = {boxRect[i].x, boxRect[i].y, boxRect[i].w, boxRect[i].h};
            }
        }
        if (velY > 0)
        {
            if (checkCollision(personRect, boxRect[i]) == true)
            {
                boxRect[i].y = posY + personRect.h;
                boxRect[i] = {boxRect[i].x, boxRect[i].y, boxRect[i].w, boxRect[i].h};
            }
        }
        if (velY < 0)
        {
            if (checkCollision(personRect, boxRect[i]) == true)
            {
                boxRect[i].y = posY - boxRect[i].h;
                boxRect[i] = {boxRect[i].x, boxRect[i].y, boxRect[i].w, boxRect[i].h};
            }
        }
        personRect = {posX, posY, personRect.w, personRect.h};
    }

}

void Person::renderPerson (SDL_Renderer* renderer, SDL_Rect& currentClip)
{
    render (renderer, posX, posY, &currentClip);
}

void Person::setVelX (int x)
{
    velX = x;
}

void Person::setVelY (int y)
{
    velY = y;
}




