#include "smallMap.h"
using std::ifstream;
using std::cout;
smallMap::smallMap()
{
    LTexture();
    boxCount = 0;
    wallCount = 0;
    goalCount = 0;
}
void smallMap::rendersmallMap(SDL_Renderer* renderer)
{
    int x = 255 , y = 0;
    for (int j = 0; j < 14; j++)
    {
        x = 255;
        for (int i = 0; i < 17; i++)
        {
            smallMapTexture[i][j].render(renderer, x, y);
            x += 20;
        }
        y += 20;
    }
    person.render (renderer, XpersonPosition, YpersonPosition);
}
void smallMap::loadsmallMapData (SDL_Renderer* renderer, string path)
{
    ifstream fi (path.c_str());
    int x = 255, y = 0, i = 0, j = 0;
    for (i = 0; i < 14; i++)
    {
         getline(fi, smallMapDataPreLoad[i]);
    }
    for (j = 0; j < 14; j++)
    {
        string stringTemp = smallMapDataPreLoad[j];
        for (i = 0; i < 17; i++)
        {
            smallMapData[i][j] = stringTemp[i];
        }
    }
    for (j = 0; j < 14; j++)
    {
        x = 255;
        for (i = 0; i < 17; i++)
        {
            if (smallMapData[i][j] == ' ')
            {
                smallMapTexture[i][j] = floor;
            }
            if (smallMapData[i][j] == '#')
            {
                smallMapTexture[i][j] = wall;
            }
            if (smallMapData[i][j] == '*')
            {
                smallMapTexture[i][j] = grass;
            }
            if (smallMapData[i][j] == '$')
            {
                smallMapTexture[i][j] = box;
            }
            if (smallMapData[i][j] == '.')
            {
                smallMapTexture[i][j] = goal;
            }
            if (smallMapData[i][j] == '@')
            {
                XpersonPosition = x;
                YpersonPosition = y;
                smallMapTexture[i][j] = floor;
            }
            if (smallMapData[i][j] == '?')
            {
                smallMapTexture[i][j] = boxOnGoal;
            }
            if (smallMapData[i][j] == '+')
            {
                XpersonPosition = x;
                YpersonPosition = y;
                smallMapTexture[i][j] = goal;
            }
            x += 20;
        }
        y += 20;
    }

}
void smallMap::resetsmallMapData ()
{
    boxCount = 0;
    wallCount = 0;
    goalCount = 0;
}

