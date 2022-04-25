#include "box.h"
using std::cout;
box::box(){}

void box::renderBox (SDL_Renderer* renderer)
{
    for (int i = 0; i < boxCount; i++)
    {
        boxTexture.render (renderer, boxRect[i].x, boxRect[i].y);
    }
}
void box::loadBoxTexture (SDL_Renderer* renderer)
{
    boxTexture.loadFromFile (renderer, "box.png");
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
}
