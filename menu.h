#ifndef menuClass
#define menuClass
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <fstream>
#include "LTexture.h"
enum menuButtonType
{
    playButton,
    levelButton,
    tutorialButton,
    creditButton,
    quitButton,
    totalMenuButton,
    playButton_mouseIn = totalMenuButton,
    levelButton_mouseIn,
    tutorialButton_mouseIn,
    creditButton_mouseIn,
    quitButton_mouseIn,
    totalMenuButton_mouseIn
};

class menu:public LTexture
{
public:
    void loadMenuButton (SDL_Renderer* rendererint,int SCREEN_WIDTH, int SCREEN_HEIGHT);
    void handleMainMenu (SDL_Event& e, SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool& quitGame);
    void renderMainMenu (SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
    void checkMouseInMenuButton ();
    void handleMainMenuButton ();
    bool mainMenu = true, chooseLevel = true, tutorial = true, credit = true, mouseInMenuButton = false, atMainMenu = true;

    int currentMenuButton;
    LTexture mainMenuBackGround;
    LTexture menuButtonTexture[totalMenuButton_mouseIn];
    SDL_Rect menuButtonRect [totalMenuButton];
    SDL_Rect mouseRect;
};

#endif // menuClass
