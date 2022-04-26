#include "wall.h"

void wall::loadWallTexture (SDL_Renderer* renderer)
{
    wallTexture.loadFromFile (renderer, "wall.png");
}

void wall::loadWallData (const Map& gameMap)
{
    wallCount = gameMap.wallCount;
    for (int i = 0; i < wallCount; i++)
    {
        XwallPosition[i] = gameMap.XwallPosition[i];
        YwallPosition[i] = gameMap.YwallPosition[i];
        wallRect[i] = {XwallPosition[i], YwallPosition[i], 50, 50};
    }
}

void wall::renderWall(SDL_Renderer* renderer)
{
    for (int i = 0; i < wallCount; i++)
    {
        wallTexture.render (renderer, wallRect[i].x, wallRect[i].y);
    }
}
