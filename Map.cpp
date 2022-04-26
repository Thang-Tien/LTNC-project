#include "Map.h"
using std::ifstream;
using std::cout;
Map::Map()
{
    LTexture();
}
void Map::renderMap(SDL_Renderer* renderer)
{
    int x = 0, y = 0;
    for (int j = 0; j < 14; j++)
    {
        x = 0;
        for (int i = 0; i < 24; i++)
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
        for (i = 0; i < 24; i++)
        {
            mapData[i][j] = stringTemp[i];
        }
    }
    for (j = 0; j < 14; j++)
    {
        x = 0;
        for (i = 0; i < 24; i++)
        {

            mapRect[i][j] = {x, y, 50, 50};
            if (mapData[i][j] == ' ')
            {
                mapTexture[i][j].loadFromFile(renderer, "floor.png");
            }
            if (mapData[i][j] == '#')
            {
                mapTexture[i][j].loadFromFile(renderer, "wall.png");
                XwallPosition [wallCount] = x;
                YwallPosition [wallCount] = y;
                wallCount ++;
            }
            if (mapData[i][j] == '*')
            {
                mapTexture[i][j].loadFromFile(renderer, "grass.png");
            }
            if (mapData[i][j] == '$')
            {
                mapTexture[i][j].loadFromFile(renderer, "floor.png");
                XboxPosition[boxCount] = x;
                YboxPosition[boxCount] = y;
                boxCount ++;
            }
            if (mapData[i][j] == '.')
            {
                mapTexture[i][j].loadFromFile(renderer, "Goal.png");
            }
            if (mapData[i][j] == '@')
            {
                mapTexture[i][j].loadFromFile(renderer, "floor.png");
                XpersonPosition = x;
                YpersonPosition = y;
            }
            x += 50;

        }
        y += 50;
    }
    if (mapData[0][0] != '*')
    {
        cout << "Failed to load map data" << '\n';
    }

}
