#include "button.h"

button::LButton()
{
    mouseIn = false;
}

void button::setPosition(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    buttonRect[backToMenuButton] = {SCREEN_WIDTH - buttonTexture[restartButton].getWidth() - buttonTexture[undoButton].getWidth() - buttonTexture[previousLevelButton].getWidth() - buttonTexture[nextLevelButton].getWidth() - buttonTexture[backToMenuButton].getWidth() - 5,
    0, buttonTexture[backToMenuButton].getWidth(), buttonTexture[backToMenuButton].getHeight()};

    buttonRect[backToMenuButton_mouseIn] = {SCREEN_WIDTH - buttonTexture[restartButton].getWidth() - buttonTexture[undoButton].getWidth() - buttonTexture[previousLevelButton].getWidth() - buttonTexture[nextLevelButton].getWidth() - buttonTexture[backToMenuButton].getWidth() - 5,
    0, buttonTexture[backToMenuButton].getWidth(), buttonTexture[backToMenuButton].getHeight()};

    buttonRect[restartButton] = {SCREEN_WIDTH - buttonTexture[restartButton].getWidth() - buttonTexture[undoButton].getWidth() - buttonTexture[previousLevelButton].getWidth() - buttonTexture[nextLevelButton].getWidth() - 4,
    0, buttonTexture[restartButton].getWidth (), buttonTexture[restartButton].getHeight()};

    buttonRect[restartButton_MouseIn] = {SCREEN_WIDTH - buttonTexture[restartButton].getWidth() - buttonTexture[undoButton].getWidth() - buttonTexture[previousLevelButton].getWidth() - buttonTexture[nextLevelButton].getWidth() - 4,
    0, buttonTexture[restartButton].getWidth(), buttonTexture[restartButton_MouseIn].getHeight()};

    buttonRect[undoButton] = {SCREEN_WIDTH - buttonTexture[undoButton].getWidth() - buttonTexture[previousLevelButton].getWidth() - buttonTexture[nextLevelButton].getWidth() - 3,
    0, buttonTexture[undoButton].getWidth(), buttonTexture[undoButton].getHeight()};

    buttonRect[undoButton_MouseIn] = {SCREEN_WIDTH - buttonTexture[undoButton].getWidth() - buttonTexture[previousLevelButton].getWidth() - buttonTexture[nextLevelButton].getWidth() - 3,
    0, buttonTexture[undoButton].getWidth(), buttonTexture[undoButton].getHeight()};

    buttonRect[previousLevelButton] = {SCREEN_WIDTH - buttonTexture[previousLevelButton].getWidth() - buttonTexture[nextLevelButton].getWidth() - 2,
    0, buttonTexture[previousLevelButton].getWidth(), buttonTexture[previousLevelButton].getHeight()};

    buttonRect[previousLevelButton_MouseIn] = {SCREEN_WIDTH - buttonTexture[previousLevelButton].getWidth() - buttonTexture[nextLevelButton].getWidth() - 2,
    0, buttonTexture[previousLevelButton].getWidth(), buttonTexture[previousLevelButton].getHeight()};

    buttonRect[nextLevelButton] = {SCREEN_WIDTH - buttonTexture[nextLevelButton].getWidth() - 1,
    0, buttonTexture[nextLevelButton].getWidth(), buttonTexture[nextLevelButton].getHeight()};

    buttonRect[nextLevelButton_MouseIn] = {SCREEN_WIDTH - buttonTexture[nextLevelButton].getWidth() - 1,
    0, buttonTexture[nextLevelButton].getWidth(), buttonTexture[nextLevelButton].getHeight()};
}

void button::renderButton(SDL_Renderer* renderer)
{
    for (int i = 0; i < totalButton_mouseOut; i++)
    {
        buttonTexture[i].render (renderer, buttonRect[i].x, buttonRect[i].y);
    }
}

void button::loadButton (SDL_Renderer* renderer)
{
    // load button image
    buttonTexture[backToMenuButton].loadFromFile (renderer, "buttons/CasualIcons_Locked_006.png");
    buttonTexture[backToMenuButton_mouseIn].loadFromFile (renderer, "buttons/CasualIcons_006.png");

    buttonTexture[restartButton].loadFromFile (renderer, "buttons/CasualIcons_Locked_004.png");
    buttonTexture[restartButton_MouseIn].loadFromFile (renderer, "buttons/CasualIcons_004.png");

    buttonTexture[nextLevelButton].loadFromFile (renderer, "buttons/CasualIcons_Locked_025.png");
    buttonTexture[nextLevelButton_MouseIn].loadFromFile (renderer, "buttons/CasualIcons_025.png");

    buttonTexture[previousLevelButton].loadFromFile (renderer, "buttons/CasualIcons_Locked_026.png");
    buttonTexture[previousLevelButton_MouseIn].loadFromFile (renderer, "buttons/CasualIcons_026.png");

    buttonTexture[undoButton].loadFromFile (renderer, "buttons/CasualIcons_Locked_023.png");
    buttonTexture[undoButton_MouseIn].loadFromFile (renderer, "buttons/CasualIcons_023.png");
}
void button::checkMouseIn ()
{
    int x, y;
    SDL_GetMouseState (&x, &y);
    mouseRect = {x, y, 1, 1};
    mouseIn = false;
    for (int i = 0; i < totalButton_mouseOut; i++)
    {
        if (checkCollision (mouseRect, buttonRect[i]) == true)
        {
            currentButton = i;
            mouseIn = true;
            break;
        }
    }
}

void button::handleMouseIn(SDL_Renderer* renderer, SDL_Event& e)
{

    switch (currentButton)
    {
    case backToMenuButton:
    {
        buttonTexture[backToMenuButton_mouseIn].render (renderer, buttonRect[backToMenuButton_mouseIn].x, buttonRect[backToMenuButton_mouseIn].y);
        break;
    }
    case restartButton:
    {
        buttonTexture[restartButton_MouseIn].render (renderer, buttonRect[restartButton_MouseIn].x, buttonRect[restartButton_MouseIn].y);
        break;
    }
    case undoButton:
    {
        buttonTexture[undoButton_MouseIn].render (renderer, buttonRect[undoButton_MouseIn].x, buttonRect[undoButton_MouseIn].y);
        break;
    }
    case previousLevelButton:
    {
        buttonTexture[previousLevelButton_MouseIn].render (renderer, buttonRect[previousLevelButton_MouseIn].x, buttonRect[previousLevelButton_MouseIn].y);
        break;
    }
    case nextLevelButton:
    {
        buttonTexture[nextLevelButton_MouseIn].render (renderer, buttonRect[nextLevelButton_MouseIn].x, buttonRect[nextLevelButton_MouseIn].y);
        break;
    }
    }

}
void button::handleButton(Map& gameMap, bool& quit, int& level, menu& Menu)
{
    switch (currentButton)
    {
    case backToMenuButton:
    {
        quit = true;
        gameMap.resetMapData();
        Menu.atMainMenu = true;
        Menu.mainMenu = true;
        break;
    }
    case restartButton:
    {
        quit = true;
        gameMap.resetMapData();
        break;
    }
    case undoButton:
    {
        last ++;
        break;
    }
    case previousLevelButton:
    {
        quit = true;
        level --;
        if (level < 0)
        {
            level = 0;
        }
        gameMap.resetMapData();
        break;
    }
    case nextLevelButton:
    {
        quit = true;
        level ++;
        gameMap.resetMapData();
        break;
    }
    }
}
