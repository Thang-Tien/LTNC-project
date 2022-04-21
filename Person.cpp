#include "Person.h"
Person::Person()
{
    LTexture();

    velX = 0;
    velY = 0;
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
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
        {
            velY += 1;
            break;

        }
        case SDLK_DOWN:
        {
            velY -= 1;
            break;

        }
        case SDLK_LEFT:
        {
            velX += 1;
            break;

        }
        case SDLK_RIGHT:
        {

            velX -= 1;
            break;
        }
        }
    }
}

void Person::move(SDL_Rect& personRect, SDL_Rect& boxRect)
{
    posX += velX;
    personRect = {posX, posY, personRect.w, personRect.h};
    boxRect = {boxRect.x, boxRect.y, boxRect.w, boxRect.h};
    if (velX > 0)
    {
        if (checkCollision(personRect, boxRect) == true)
        {
            boxRect.x = posX + personRect.w;
            boxRect = {boxRect.x, boxRect.y, boxRect.w, boxRect.h};
        }
    }
    if (velX < 0)
    {
        if (checkCollision(personRect, boxRect) == true)
        {
            boxRect.x = posX - boxRect.w;
            boxRect = {boxRect.x, boxRect.y, boxRect.w, boxRect.h};
        }
    }
    posY += velY;
    personRect = {posX, posY, personRect.w, personRect.h};
    if (velY > 0)
    {
        if (checkCollision(personRect, boxRect) == true)
        {
            boxRect.y = posY + 32;
            boxRect = {boxRect.x, boxRect.y, boxRect.w, boxRect.h};
        }
    }
    if (velY < 0)
    {
        if (checkCollision(personRect, boxRect) == true)
        {
            boxRect.y = posY - boxRect.h;
            boxRect = {boxRect.x, boxRect.y, boxRect.w, boxRect.h};
        }
    }
}

void Person::renderPerson (SDL_Renderer* renderer, SDL_Rect& currentClip)
{
    render (renderer, posX, posY, &currentClip);
}




