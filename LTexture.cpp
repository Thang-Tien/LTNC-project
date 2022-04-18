#include "LTexture.h"

using std::cout;
LTexture::LTexture()
{
    texture = NULL;
    posX = 0;
    posY = 0;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    free();
}

bool LTexture::loadFromFile (SDL_Renderer* renderer, string path)
{
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load (path.c_str());
    if (loadedSurface == NULL)
    {
        cout << "Unable to load image from " << path.c_str() << "Errror: " << SDL_GetError() << '\n';
    }
    else
    {
        SDL_SetColorKey (loadedSurface, SDL_TRUE, SDL_MapRGB (loadedSurface -> format, 255, 255, 255));
        newTexture = SDL_CreateTextureFromSurface (renderer, loadedSurface);
        if (newTexture == NULL)
        {
            cout << "Unable to create texture from " << path.c_str() << " " << "Error: " << SDL_GetError() << '\n';
        }
        else
        {
            mWidth = loadedSurface -> w;
            mHeight = loadedSurface -> h;
        }
        SDL_FreeSurface (loadedSurface);
    }
    texture = newTexture;
    return texture != NULL;
}

bool LTexture::loadFromRenderedText (SDL_Renderer* renderer, TTF_Font* font,string textureText, SDL_Color textColor)
{
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = TTF_RenderText_Solid (font, textureText.c_str(), textColor);
    if (loadedSurface == NULL)
    {
        cout << "Unable to load text from " << ", Errror: " << SDL_GetError() << '\n';
    }
    else
    {
        SDL_SetColorKey (loadedSurface, SDL_TRUE, SDL_MapRGB (loadedSurface -> format, 255, 255, 255));
        newTexture = SDL_CreateTextureFromSurface (renderer, loadedSurface);
        if (newTexture == NULL)
        {
            cout << "Unable to create texture from " << ", Error: " << SDL_GetError() << '\n';
        }
        else
        {
            mWidth = loadedSurface -> w;
            mHeight = loadedSurface -> h;
        }
        SDL_FreeSurface (loadedSurface);
    }
    texture = newTexture;
    return newTexture != NULL;
}

void LTexture:: free()
{
    if (texture != NULL)
    {
        SDL_DestroyTexture (texture);
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod (texture, red, green, blue);
}

void LTexture::setBlendMode (SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(texture, blending);
}

void LTexture::setAlpha (Uint8 alpha)
{
    SDL_SetTextureAlphaMod (texture, alpha);
}

//Render
void LTexture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    if (clip != NULL)
    {
        renderQuad.w = clip -> w;
        renderQuad.h = clip -> h;
    }
    SDL_RenderCopyEx( renderer, texture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}
int LTexture::getPosX ()
{
    return posX;
}

int LTexture::getPosY ()
{
    return posY;
}
void LTexture::setPosX (int x)
{
    posX = x;
}
void LTexture::setPosY (int y)
{
    posY = y;
}



