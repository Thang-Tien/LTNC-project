#include "box.h"
using std::cout;
box::box(){}

void box::renderBox (SDL_Renderer* renderer)
{
    for (int i = 0; i < boxCount; i++)
    {
        boxTexture.render (renderer, boxRect[i].x, boxRect[i].y);
    }
    for (int i = 0; i < boxCount; i++)
    {
        for (int j = 0; j < goalCount; j++)
        {
            if (XgoalPosition[j] == boxRect[i].x && YgoalPosition[j] == boxRect[i].y)
            {
                scoredGoals[j] = true;
                boxWinTexture.render(renderer, XgoalPosition[j], YgoalPosition[j]);
            }
        }
    }

}
void box::loadBoxTexture (SDL_Renderer* renderer)
{
    boxTexture.loadFromFile (renderer, "box.png");
    boxWinTexture.loadFromFile (renderer, "box_win.png");
}
void box::loadBoxData (const Map& gameMap)
{
    boxCount = gameMap.boxCount;
    for (int i = 0; i < boxCount; i++)
    {
        XboxPosition [i] = gameMap.XboxPosition[i];
        YboxPosition [i] = gameMap.YboxPosition[i];
        boxRect[i] = {XboxPosition[i], YboxPosition[i], 50, 50};
    }
    goalCount = gameMap.goalCount;
    for (int i = 0; i < goalCount; i++)
    {
        XgoalPosition [i] = gameMap.XgoalPosition[i];
        YgoalPosition [i] = gameMap.YgoalPosition[i];
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

