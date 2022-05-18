#include "menu.h"

void menu::loadMenuButton (SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    mainMenuBackGround.loadFromFile (renderer, "images/main_menu.png");

    menuButtonTexture [playButton].loadFromFile (renderer, "buttons/CasualButtons_Locked_001.png");
    menuButtonTexture [playButton_mouseIn].loadFromFile (renderer, "buttons/CasualButtons_001.png");
    menuButtonTexture [levelButton].loadFromFile (renderer, "buttons/levels_mouse_out.png");
    menuButtonTexture [levelButton_mouseIn].loadFromFile (renderer, "buttons/levels_mouse_in.png");
    menuButtonTexture [tutorialButton].loadFromFile (renderer, "buttons/CasualButtons_Locked_004.png");
    menuButtonTexture [tutorialButton_mouseIn].loadFromFile (renderer, "buttons/CasualButtons_004.png");
    menuButtonTexture [creditButton].loadFromFile (renderer, "buttons/credits_mouse_out.png");
    menuButtonTexture [creditButton_mouseIn].loadFromFile (renderer, "buttons/credits_mouse_in.png");
    menuButtonTexture [quitButton].loadFromFile (renderer, "buttons/CasualButtons_Locked_009.png");
    menuButtonTexture [quitButton_mouseIn].loadFromFile (renderer, "buttons/CasualButtons_009.png");

    int menuButtonPosY = 300;
    for (int i = 0; i < totalMenuButton; i++)
    {
        menuButtonRect[i] = {SCREEN_WIDTH/2 - menuButtonTexture[i].getWidth()/2, menuButtonPosY, menuButtonTexture[i].getWidth(), menuButtonTexture[i].getHeight()};
        menuButtonPosY += menuButtonTexture[i].getHeight() + 10;
    }
}
void menu::handleMainMenu (SDL_Event& e, SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, bool& quitGame)
{
    checkMouseInMenuButton();
    if (mouseInMenuButton == true)
    {
        switch (currentMenuButton)
        {
        case playButton:
        {
            menuButtonTexture [playButton_mouseIn].render (renderer, menuButtonRect[playButton].x, menuButtonRect[playButton].y);
            break;
        }
        case levelButton:
        {
            menuButtonTexture [levelButton_mouseIn].render (renderer, menuButtonRect[levelButton].x, menuButtonRect[levelButton].y);
            break;
        }
        case tutorialButton:
        {
            menuButtonTexture [tutorialButton_mouseIn].render (renderer, menuButtonRect[tutorialButton].x, menuButtonRect[tutorialButton].y);
            break;
        }
        case creditButton:
        {
            menuButtonTexture [creditButton_mouseIn].render (renderer, menuButtonRect[creditButton].x, menuButtonRect[creditButton].y);
            break;
        }
        case quitButton:
        {
            menuButtonTexture [quitButton_mouseIn].render (renderer, menuButtonRect[quitButton].x, menuButtonRect[quitButton].y);
            break;
        }
        }
    }
    while (SDL_PollEvent (&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            atMainMenu = false;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            if (mouseInMenuButton == true)
            {
                switch (currentMenuButton)
                {
                case playButton:
                {
                    atMainMenu = false;
                    break;
                }
                case levelButton:
                {
                    break;
                }
                case tutorialButton:
                {
                    break;
                }
                case creditButton:
                {
                    break;
                }
                case quitButton:
                {
                    atMainMenu = false;
                    quitGame = true;
                    break;
                }
                }
            }
        }
    }
}

void menu::renderMainMenu (SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    mainMenuBackGround.render (renderer, 0, 0);
    int menuButtonPosY = 300;
    for (int i = 0; i < totalMenuButton; i++)
    {
        menuButtonTexture [i].render (renderer, SCREEN_WIDTH/2 - menuButtonTexture[i].getWidth()/2, menuButtonPosY);
        menuButtonPosY += menuButtonTexture[i].getHeight() + 10;
    }
}

void menu::checkMouseInMenuButton ()
{
    int x, y;
    SDL_GetMouseState (&x, &y);
    mouseRect = {x, y, 1, 1};
    mouseInMenuButton = false;
    for (int i = 0; i < totalMenuButton; i++)
    {
        if (checkCollision (mouseRect, menuButtonRect[i]) == true)
        {
            currentMenuButton = i;
            mouseInMenuButton = true;
            break;
        }
    }
}

