#include "menu.h"

// load
void menu::loadMenuButton (SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    mainMenuBackGround.loadFromFile (renderer, "images/main_menu.png");
    levelNumButton.loadFromFile (renderer, "buttons/level_button.png");
    levelNumButtonWon.loadFromFile (renderer, "buttons/level_button_won.png");
    levelNumButtonOutline.loadFromFile (renderer, "buttons/level_button_outline.png");

    backButton.loadFromFile (renderer, "buttons/CasualIcons_Locked_001.png");
    backButton_mouseIn.loadFromFile (renderer, "buttons/CasualIcons_001.png");
    deleteButton.loadFromFile (renderer, "buttons/CasualIcons_Locked_035.png");
    deleteButton_mouseIn.loadFromFile (renderer, "buttons/CasualIcons_035.png");
    yesButton.loadFromFile (renderer, "buttons/CasualButtons_Locked_006.png");
    yesButton_mouseIn.loadFromFile (renderer, "buttons/CasualButtons_006.png");
    noButton.loadFromFile (renderer, "buttons/CasualButtons_Locked_010.png");
    noButton_mouseIn.loadFromFile (renderer, "buttons/CasualButtons_010.png");

    tutorialTexture.loadFromFile (renderer, "images/tutorial.png");
    creditTexture.loadFromFile (renderer, "images/credit.png");
    warningTexture.loadFromFile (renderer, "images/warning.png");

    menuButtonTexture [playButton].loadFromFile (renderer, "buttons/CasualButtons_Locked_001.png");
    menuButtonTexture [playButton_mouseIn].loadFromFile (renderer, "buttons/CasualButtons_001.png");
    menuButtonTexture [levelButton].loadFromFile (renderer, "buttons/levels_mouse_out.png");
    menuButtonTexture [levelButton_mouseIn].loadFromFile (renderer, "buttons/levels_mouse_in.png");
    menuButtonTexture [tutorialButton].loadFromFile (renderer, "buttons/CasualButtons_Locked_008.png");
    menuButtonTexture [tutorialButton_mouseIn].loadFromFile (renderer, "buttons/CasualButtons_008.png");
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

    warningTextureRect = {SCREEN_WIDTH/2 - warningTexture.getWidth()/2, SCREEN_HEIGHT/2 - warningTexture.getHeight()/2, warningTexture.getWidth(), warningTexture.getHeight()};
    backButtonRect = {0, 0, backButton.getWidth(), backButton.getHeight()};
    deleteButtonRect = {SCREEN_WIDTH - deleteButton.getWidth(), 0, deleteButton.getWidth(), deleteButton.getHeight()};
    yesButtonRect = {225 + (200 - yesButton.getWidth ())/2, 350 + (100 - yesButton.getHeight())/2, yesButton.getWidth (), yesButton.getHeight()};
    noButtonRect = {425 + (200 - noButton.getWidth ())/2, 350 + (100 - noButton.getHeight())/2, noButton.getWidth (), noButton.getHeight()};

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

// handle
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
                    atMainMenu = false;
                    tutorial = true;
                    break;
                }
                case creditButton:
                {
                    atMainMenu = false;
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

void menu::handleLevelList (SDL_Event& e, SDL_Renderer* renderer, int& level, bool& quitGame, smallMap& preViewMap)
{

    int x, y;
    SDL_GetMouseState (&x, &y);
    mouseRect = {x, y, 1, 1};
    mouseInBackButton = false;
    if (checkCollision (mouseRect, backButtonRect) == true)
    {
        backButton_mouseIn.render (renderer, 0, 0);
        mouseInBackButton = true;
    }
    if (checkCollision (mouseRect, deleteButtonRect) == true)
    {
        deleteButton_mouseIn.render (renderer, deleteButtonRect.x, deleteButtonRect.y);
    }
    while (SDL_PollEvent (&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            choosingLevel = false;
            atMainMenu = false;
            mainMenu = false;
            quitGame = true;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            haveJustBeenConfirming = false;
            if (checkCollision (mouseRect, backButtonRect) == true)
            {
                choosingLevel = false;
                atMainMenu = true;
            }
            if (checkCollision (mouseRect, deleteButtonRect) == true)
            {
                haveJustBeenConfirming = true;
                confirming = true;
                while (confirming)
                {
                    warningTexture.render (renderer, warningTextureRect.x, warningTextureRect.y);
                    yesButton.render (renderer, yesButtonRect.x, yesButtonRect.y);
                    noButton.render (renderer, noButtonRect.x, noButtonRect.y);

                    handleConfirming (e, renderer, quitGame, preViewMap, level);
                    SDL_RenderPresent (renderer);
                }
            }
            if (mouseInLevelButton == true && haveJustBeenConfirming == false)
            {
                level = currentLevel;
                choosingLevel = false;
                atMainMenu = false;
                mainMenu = false;
            }
        }
    }
}

void menu::handleConfirming (SDL_Event& e, SDL_Renderer* renderer, bool& quitGame, smallMap& preViewMap, int& level)
{
    int x, y;
    SDL_GetMouseState (&x, &y);
    mouseRect = {x, y, 1, 1};
    mouseInYesButton = false;
    mouseInNoButton = false;
    if (checkCollision(mouseRect, yesButtonRect) == true)
    {
        yesButton_mouseIn.render (renderer, yesButtonRect.x, yesButtonRect.y);
        mouseInYesButton = true;
    }
    if (checkCollision(mouseRect, noButtonRect) == true)
    {
        noButton_mouseIn.render (renderer, noButtonRect.x, noButtonRect.y);
        mouseInNoButton = true;
    }
    while (SDL_PollEvent (&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            confirming = false;
            quitGame = false;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            if (mouseInYesButton == true)
            {
                deleteScore ();
                checkLevelWon ();
                renderLevelList (renderer, preViewMap, level);
                confirming = false;
            }
            else if (mouseInNoButton == true)
            {
                confirming = false;
            }
        }
    }
}

void menu::handleTutorial (SDL_Event& e, SDL_Renderer* renderer, bool& quitGame)
{
    int x, y;
    SDL_GetMouseState (&x, &y);
    mouseRect = {x, y, 1, 1};
    mouseInBackButton  = false;
    if (checkCollision (mouseRect, backButtonRect) == true)
    {
        backButton_mouseIn.render (renderer, 0, 0);
        mouseInBackButton = true;
    }

    while (SDL_PollEvent (&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            tutorial = false;
            atMainMenu = false;
            mainMenu = false;
            quitGame = true;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            if (mouseInBackButton == true)
            {
                tutorial = false;
                atMainMenu = true;
            }
        }
    }
}

void menu::handleCredit (SDL_Event& e, SDL_Renderer* renderer, bool& quitGame)
{
    int x, y;
    SDL_GetMouseState (&x, &y);
    mouseRect = {x, y, 1, 1};
    mouseInBackButton  = false;
    if (checkCollision (mouseRect, backButtonRect) == true)
    {
        backButton_mouseIn.render (renderer, 0, 0);
        mouseInBackButton = true;
    }

    while (SDL_PollEvent (&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            credit = false;
            atMainMenu = false;
            mainMenu = false;
            quitGame = true;
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            if (mouseInBackButton == true)
            {
                tutorial = false;
                credit = false;
                atMainMenu = true;
            }
        }
    }
}

// check
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

// render
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

void menu::renderLevelList (SDL_Renderer* renderer, smallMap& preViewMap, int& level)
{
    int x = 15, y = 310, levelNum = 0;
    checkMouseInLevelButton ();
    if (mouseInLevelButton == true)
    {
        // render preview map
        preViewMap.loadsmallMapData (renderer, "levels/" + std::to_string (currentLevel) + ".txt");
        preViewMap.rendersmallMap (renderer);

        // render level out line
        levelNumButtonOutline.render (renderer, levelRect[currentLevel - 1].x - (levelNumButtonOutline.getWidth() - levelRect[currentLevel - 1].w)/2,
                                                levelRect[currentLevel - 1].y - (levelNumButtonOutline.getHeight() - levelRect[currentLevel - 1].h)/2);
    }

    for (int i = 0; i < 7; i++)
    {
        x = 15;
        for (int j = 0; j < 15; j++)
        {
            // render won level in green
            if (levelWon[levelNum] == false) levelNumButton.render (renderer, x, y);
            else levelNumButtonWon.render (renderer, x, y);

            // render level number
            levelNumText[levelNum].render (renderer, x + levelNumButton.getWidth()/2 - levelNumText[levelNum].getWidth()/2,
                                                     y + levelNumButton.getHeight()/2 - levelNumText[levelNum].getHeight()/2);
            levelRect[levelNum] = {x, y, levelNumButton.getWidth(), levelNumButton.getHeight()};

            levelNum ++;
            x += 55;
        }
        y += 55;
    }
}

void menu::deleteScore ()
{
    for (int i = 1; i <= 105; i++)
    {
        std::ofstream fo ("scores/" + std::to_string(i) + ".txt");
        fo << 0 << " " << 0;
    }

}





