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
    // load texture
    void loadMenuButton (SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
    void loadLevelNum (SDL_Renderer* renderer);

    // handle
    void handleMainMenu (SDL_Event& e, SDL_Renderer* renderer, bool& quitGame);
    void handleLevelList (SDL_Event& e, SDL_Renderer* renderer, int& level, bool& quitGame);
    void handleTutorial (SDL_Event& e, SDL_Renderer* renderer, bool& quitGame);
    void handleCredit (SDL_Event& e, SDL_Renderer* renderer, bool& quitGame);
    void handleMainMenuButton ();

    // render
    void renderChoosingLevel ();
    void renderMainMenu (SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT);
    void renderLevelList (SDL_Renderer* renderer);

    // check
    void checkMouseInMenuButton ();
    void checkMouseInLevelButton ();
    void checkLevelWon ();

    bool mainMenu = true, tutorial = false, credit = false, atMainMenu = true, choosingLevel = false,
         mouseInMenuButton = false, mouseInLevelButton = false, mouseInBackButton = false;
    bool levelWon [105];

    int currentMenuButton, currentLevel;

    LTexture mainMenuBackGround, tutorialTexture, creditTexture;

    LTexture levelNumButton, levelNumButtonWon, levelNumButtonOutline;
    LTexture backButton, backButton_mouseIn;
    LTexture menuButtonTexture[totalMenuButton_mouseIn];
    LTexture levelNumText [105];
    TTF_Font* levelNumFont = NULL;

    SDL_Color levelNumColor = {0, 0, 0};
    SDL_Rect levelRect [105];
    SDL_Rect menuButtonRect [totalMenuButton];
    SDL_Rect mouseRect;
    SDL_Rect backButtonRect;
};

#endif // menuClass
