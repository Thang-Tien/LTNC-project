#include "Map.h"
using std::ifstream;
using std::cout;
Map::Map()
{
    LTexture();
    boxCount = 0;
    wallCount = 0;
    goalCount = 0;
}
void Map::renderMap(SDL_Renderer* renderer)
{
    int x = 0, y = 0;
    for (int j = 0; j < 14; j++)
    {
        x = 0;
        for (int i = 0; i < 17; i++)
        {
            mapTexture[i][j].render(renderer, x, y);
            x += 50;
        }
        y += 50;
    }
}
void Map::loadMapData (SDL_Renderer* renderer, string path)
{
    ifstream fi (path.c_str());
    int x = 0, y = 0, i = 0, j = 0;
    for (i = 0; i < 14; i++)
    {
         getline(fi, mapDataPreLoad[i]);
    }
    for (j = 0; j < 14; j++)
    {
        string stringTemp = mapDataPreLoad[j];
        for (i = 0; i < 17; i++)
        {
            mapData[i][j] = stringTemp[i];
        }
    }
    for (j = 0; j < 14; j++)
    {
        x = 0;
        for (i = 0; i < 17; i++)
        {
            mapRect[i][j] = {x, y, 50, 50};
            if (mapData[i][j] == ' ')
            {
                mapTexture[i][j].loadFromFile(renderer, "images/floor.png");
            }
            if (mapData[i][j] == '#')
            {
                XwallPosition [wallCount] = x;
                YwallPosition [wallCount] = y;
                wallCount ++;
            }
            if (mapData[i][j] == '*')
            {
                mapTexture[i][j].loadFromFile(renderer, "images/grass.png");
            }
            if (mapData[i][j] == '$')
            {
                mapTexture[i][j].loadFromFile(renderer, "images/floor.png");
                XboxPosition[boxCount] = x;
                YboxPosition[boxCount] = y;
                boxCount ++;
            }
            if (mapData[i][j] == '.')
            {
                mapTexture[i][j].loadFromFile(renderer, "images/Goal.png");
                XgoalPosition[goalCount] = x;
                YgoalPosition[goalCount] = y;
                goalCount ++;
            }
            if (mapData[i][j] == '@')
            {
                mapTexture[i][j].loadFromFile(renderer, "images/floor.png");
                XpersonPosition = x;
                YpersonPosition = y;
            }
            if (mapData[i][j] == '?')
            {
                mapTexture[i][j].loadFromFile(renderer, "images/Goal.png");

                XboxPosition[boxCount] = x;
                YboxPosition[boxCount] = y;
                boxCount ++;

                XgoalPosition[goalCount] = x;
                YgoalPosition[goalCount] = y;
                goalCount ++;
            }
            if (mapData[i][j] == '+')
            {
                mapTexture[i][j].loadFromFile(renderer, "images/Goal.png");
                XpersonPosition = x;
                YpersonPosition = y;

                XgoalPosition[goalCount] = x;
                YgoalPosition[goalCount] = y;
                goalCount ++;
            }
            x += 50;

        }
        y += 50;
    }

}
void Map::resetMapData ()
{
    boxCount = 0;
    wallCount = 0;
    goalCount = 0;
}
