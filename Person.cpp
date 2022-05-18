#include "Person.h"
using std::cout;
using std::swap;
Person::Person()
{
    velX = 0;
    velY = 0;
    distance = 0;
    goHorizontal = false;
    goVertical = false;
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
            goVertical = true;
            break;
        }
        case SDLK_DOWN:
        {
            velY += 1;
            direction = 0;
            goVertical = true;
            break;
        }
        case SDLK_LEFT:
        {
            velX -= 1;
            direction = 1;
            goHorizontal = true;
            break;
        }
        case SDLK_RIGHT:
        {
            velX += 1;
            direction = 2;
            goHorizontal = true;
            break;
        }
        default:
        {
            goVertical = false;
            goHorizontal = false;
        }
        }
    }

}

void Person::moveAndCheckCollision (SDL_Renderer* renderer, SDL_Rect& personRect, SDL_Rect boxRect[]  , int& boxCount, SDL_Rect wallRect[], int& wallCount)
{
    posX += velX;
    posY += velY;

    // person pushes box
    for (int i = 0; i < boxCount; i++)
    {
        personRect = {posX, posY, personRect.w, personRect.h};
        if (checkCollision(personRect, boxRect[i]) == true)
        {
            if (velX > 0)
            {
                boxRect[i].x = posX + personRect.w;

            }
            if (velX < 0)
            {
                boxRect[i].x = posX - boxRect[i].w;
            }
            if (velY > 0)
            {

                boxRect[i].y = posY + personRect.h;
            }
            if (velY < 0)
            {
                boxRect[i].y = posY - boxRect[i].h;
            }
        }
    }

    // box vs box collision check
    if (goHorizontal == true)
    {
        // sort box by x
        for (int i = 0; i < boxCount; i++)
        {
            for (int j = i + 1; j < boxCount; j++)
            {
                if (boxRect[j].x < boxRect[i].x)
                {
                    swap (boxRect[i], boxRect[j]);
                }
            }
        }
        // check box vs box collision horizontal
        for (int i = 0; i < boxCount; i++)
        {
            personRect = {posX, posY, personRect.w, personRect.h};
            for (int j = i + 1; j < boxCount; j++)
            {
                if (checkCollision (boxRect[i], boxRect[j]) == true)
                {
                    if (velX > 0)
                    {
                        boxRect[i].x = boxRect[j].x - 50;
                        posX = boxRect[j].x - 100;
                    }
                    if (velX < 0)
                    {
                        boxRect[j].x = boxRect[i].x + 50;
                        posX = boxRect[i].x + 100;
                    }
                    personRect = {posX, posY, personRect.w, personRect.h};
                }
            }
        }
    }
    else if (goVertical == true)
    {
        // sort box for y
        for (int i = 0; i < boxCount; i++)
        {
            for (int j = i + 1; j < boxCount; j++)
            {
                if (boxRect[j].y < boxRect[i].y)
                {
                    swap (boxRect[i], boxRect[j]);
                }
            }
        }
        // check box vs box collision vertical
        for (int i = 0; i < boxCount; i++)
        {
            personRect = {posX, posY, personRect.w, personRect.h};
            for (int j = i + 1; j < boxCount; j++)
            {
                if (checkCollision (boxRect[i], boxRect[j]) == true)
                {
                    if (velY > 0)
                    {
                        boxRect[i].y = boxRect[j].y - 50;
                        posY = boxRect[j].y - 100;
                    }
                    if (velY < 0)
                    {
                        boxRect[j].y = boxRect[i].y + 50;
                        posY = boxRect[i].y + 100;
                    }
                    personRect = {posX, posY, personRect.w, personRect.h};
                }
            }
        }
    }
    // person vs wall collision check
    for (int i = 0; i < wallCount; i++)
    {
        if (checkCollision (personRect, wallRect[i]) == true)
        {
            posX -= velX;
            posY -= velY;
            personRect = {posX, posY, personRect.w, personRect.h};
        }
    }

    // box vs wall collision check
    for (int i = 0; i < boxCount; i++)
    {
        for (int j = 0; j < wallCount; j++)
        {
            if (checkCollision (boxRect[i], wallRect[j]) == true)
            {
                if (velX > 0)
                {
                    boxRect[i].x = wallRect[j].x - 50;
                    posX = boxRect[i].x - 50;
                }
                if (velX < 0)
                {
                    boxRect[i].x = wallRect[j].x + 50;
                    posX = boxRect[i].x + 50;
                }
                if (velY > 0)
                {
                    boxRect[i].y = wallRect[j].y - 50;
                    posY = boxRect[i].y - 50;
                }
                if (velY < 0)
                {
                    boxRect[i].y = wallRect[j].y + 50;
                    posY = boxRect[i].y + 50;
                }
                personRect = {posX, posY, personRect.w, personRect.h};
            }
        }
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




