#include "music.h"

void music::loadMusic()
{
    themeMusic = Mix_LoadMUS ("music/theme-song.mp3");
    if (themeMusic == NULL)
    {
        std::cout << "Failed to load theme music, Error: " << Mix_GetError() << '\n';
    }
}
