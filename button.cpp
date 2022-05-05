#include "button.h"

button::LButton()
{
    buttonPosition.x = 0;
    buttonPosition.y = 0;
}

void button::setPosition( int x, int y )
{
     buttonPosition.x = x;
     buttonPosition.y = y;
}

void button::renderButton(SDL_Renderer* renderer)
{
    buttonTexture.render (renderer, buttonPosition.x, buttonPosition.y);
}

void button::loadButton (SDL_Renderer* renderer, string path)
{
    buttonTexture.loadFromFile (renderer, path.c_str());
}

