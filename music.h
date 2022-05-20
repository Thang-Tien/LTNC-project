#ifndef musicClass
#define musicClass
#include <SDL_mixer.h>
#include <iostream>
#include "LTexture.h"

class music:public LTexture
{
public:
    void loadMusic ();

    Mix_Music* themeMusic;
};
#endif // musicClass
