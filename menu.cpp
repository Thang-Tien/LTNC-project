#include "menu.h"

void menu::loadMenuButton (SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    mainMenuBackGround.loadFromFile (renderer, "images/main_menu.png");
    levelNumButton.loadFromFile (renderer, "buttons/level_button.png");
    levelNumButtonWon.loadFromFile (renderer, "buttons/level_button_won.png");
    levelNumButtonOutline.loadFromFile (renderer, "buttons/level_button_outline.png");

    backButton.loadFromFile (renderer, "buttons/CasualIcons_Locked_001.png");
    backButton_mouseIn.loadFromFile (renderer, "buttons/CasualIcons_001.png");

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

    int menuButtonPosY = 320;
    for (int i = 0; i < totalMenuButton; i++)
    {
        menuButtonRect[i] = {SCREEN_WIDTH/2 - menuButtonTexture[i].getWidth()/2, menuButtonPosY, menuButtonTexture[i].getWidth(), menuButtonTexture[i].getHeight()};
        menuButtonPosY += menuButtonTexture[i].getHeight() + 10;
    }

    backButtonRect = {0, 0, backButton.getWidth(), backButton.getHeight()};
}

void menu::loadLevelNum (SDL_Renderer* renderer)
{
    int levelNum = 0;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            levelNumText [levelNum].loadFromRenderedText (renderer, levelNumFont, std::to_string (levelNum + 1), levelNumColor);
            levelNum ++;
        }
    }
}

void menu::handleMainMenu (SDL_Event& e, SDL_Renderer* renderer, bool& quitGame)
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
            mainMenu = false;
            quitGame = true;
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
                    mainMenu = false;
                    break;
                }
                case levelButton:
                {
                    atMainMenu = false;
                    choosingLevel = true;
                    break;
                }
                case tutorialButton:
                {
                    tutorial = true;
                    break;
                }
                case creditButton:
                {
                    credit = true;
                    break;
                }
                case quitButton:
                {
                    atMainMenu = false;
                    mainMenu = false;
                    quitGame = true;
                    break;
                }
                }
            }
        }
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

void menu::checkMouseInLevelButton ()
{
    int x, y;
    SDL_GetMouseState (&x, &y);
    mouseRect = {x, y, 1, 1};
    mouseInLevelButton = false;
    for (int i = 0; i < 105; i++)
    {
        if (checkCollision (mouseRect, levelRect[i]) == true)
        {
            currentLevel = i + 1;
            mouseInLevelButton = true;
            break;
        }
    }
}

void menu::checkLevelWon ()
{
    int levelNum = 1, bestSteps;
    for (int i = 0; i < 105; i++)
    {
        std::ifstream fi ("scores/" + std::to_string (levelNum) + ".txt");
        fi >> bestSteps;
        if (bestSteps == 0)
        {
            levelWon[i] = false;
        }
        else levelWon[i] = true;
        levelNum ++;
    }
}

void menu::renderMainMenu (SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    mainMenuBackGround.render (renderer, 0, 0);
    int menuButtonPosY = 320;
    for (int i = 0; i < totalMenuButton; i++)
    {
        menuButtonTexture [i].render (renderer, SCREEN_WIDTH/2 - menuButtonTexture[i].getWidth()/2, menuButtonPosY);
        menuButtonPosY += menuButtonTexture[i].getHeight() + 10;
    }
}

void menu::renderLevelList (SDL_Renderer* renderer)
{
    int x = 15, y = 310, levelNum = 0;
    checkMouseInLevelButton ();
    if (mouseInLevelButton == true)
    {
        levelNumButtonOutline.render (renderer, levelRect[currentLevel - 1].x - (levelNumButtonOutline.getWidth() - levelRect[currentLevel - 1].w)/2,
                                                levelRect[currentLevel - 1].y - (levelNumButtonOutline.getHeight() - levelRect[currentLevel - 1].h)/2);
    }
    for (int i = 0; i < 7; i++)
    {
        x = 15;
        for (int j = 0; j < 15; j++)
        {
            if (levelWon[levelNum] == false) levelNumButton.render (renderer, x, y);
            else levelNumButtonWon.render (renderer, x, y);
            levelNumText[levelNum].render (renderer, x + levelNumButton.getWidth()/2 - levelNumText[levelNum].getWidth()/2,
                                                     y + levelNumButton.getHeight()/2 - levelNumText[levelNum].getHeight()/2);
            levelRect[levelNum] = {x, y, levelNumButton.getWidth(), levelNumButton.getHeight()};
            levelNum ++;
            x += 55;
        }
        y += 55;
    }
}

void menu::handleLevelList (SDL_Event& e, SDL_Renderer* renderer, int& level)
{

    int x, y;
    SDL_GetMouseState (&x, &y);
    mouseRect = {x, y, 1, 1};
    if (checkCollision (mouseRect, backButtonRect) == true)
    {
        backButton_mouseIn.render (renderer, 0, 0);
        mouseInBackButton = true;
    }

    while (SDL_PollEvent (&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            choosingLevel = false;
            atMainMenu = false;
            mainMenu = false;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            if (checkCollision (mouseRect, backButtonRect) == true)
            {
                choosingLevel = false;
                atMainMenu = true;
            }
            if (mouseInLevelButton == true)
            {
                level = currentLevel;
                choosingLevel = false;
                atMainMenu = false;
                mainMenu = false;
            }
        }
    }
}



