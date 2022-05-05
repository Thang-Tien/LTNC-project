#include "box.h"
using std::swap;
using std::cout;
box::box()
{
    boxCount = 0;
    goalCount = 0;
}

void box::renderBox (SDL_Renderer* renderer)
{
    for (int i = 0; i < boxCount; i++)
    {
        boxTexture.render (renderer, boxRect[i].x, boxRect[i].y);
    }
    for (int j = 0; j < goalCount; j++)
    {
        for (int i = 0; i < boxCount; i++)
        {
            if (goalRect[j].x == boxRect[i].x && goalRect[j].y == boxRect[i].y)
            {
                scoredGoals[j] = true;
                boxWinTexture.render(renderer, goalRect[j].x,goalRect[j].y);
                break;
            }
            else
            {
                scoredGoals[j] = false;
            }
        }
    }
}
void box::loadBoxTexture (SDL_Renderer* renderer)
{
    boxTexture.loadFromFile (renderer, "images/box.png");
    boxWinTexture.loadFromFile (renderer, "images/box_win.png");
}
void box::loadBoxData (const Map& gameMap)
{
    boxCount = gameMap.boxCount;
    for (int i = 0; i < boxCount; i++)
    {
        boxRect[i] = {gameMap.XboxPosition[i], gameMap.YboxPosition[i], 50, 50};
    }
    goalCount = gameMap.goalCount;
    for (int i = 0; i < goalCount; i++)
    {
        goalRect[i] = {gameMap.XgoalPosition[i], gameMap.YgoalPosition[i], 50, 50};
        scoredGoals[i] = false;
    }
}
bool box::winCheck ()
{
    for (int i = 0; i < goalCount; i++)
    {
        if (scoredGoals [i] == false)
        {
            return false;
        }
    }
    return true;
}
void box::sortBoxByX()
{
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
}

void box::sortBoxByY()
{
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
}

