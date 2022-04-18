#ifndef LTEXTURECLASS__
#define LTEXTURECLASS__
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
using std::string;
class LTexture
{
public:
    LTexture ();
    ~LTexture ();
    bool loadFromFile (SDL_Renderer* renderer, string path);
    bool loadFromRenderedText (SDL_Renderer* renderer, TTF_Font* font, string textureText, SDL_Color textColor);
    void free();
    void setColor (Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode (SDL_BlendMode blending);
    void setAlpha (Uint8 alpha);
    void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
    int getWidth();
    int getHeight ();

private:
    SDL_Texture* texture;
    int mWidth;
    int mHeight;
};
#endif // LTEXTURECLASS__
