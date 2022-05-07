#include "button.h"
button::LButton()
{
    mouseIn = false;
}

void button::setPosition(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    int restartButton_Width = 60, undoButton_Width = 60,
        previousLevelButton_Width =  109,
        nextLevelButton_Width =  109;
    buttonRect[restartButton] = {SCREEN_WIDTH - restartButton_Width - undoButton_Width - previousLevelButton_Width - nextLevelButton_Width - 4, 0, restartButton_Width, 60};
    buttonRect[restartButton_MouseIn] = {SCREEN_WIDTH - restartButton_Width - undoButton_Width - previousLevelButton_Width - nextLevelButton_Width - 4, 0, restartButton_Width, 60};
    buttonRect[undoButton] = {SCREEN_WIDTH - undoButton_Width - previousLevelButton_Width - nextLevelButton_Width - 3, 0, undoButton_Width, 60};
    buttonRect[undoButton_MouseIn] = {SCREEN_WIDTH - undoButton_Width - previousLevelButton_Width - nextLevelButton_Width - 3, 0, undoButton_Width, 60};
    buttonRect[previousLevelButton] = {SCREEN_WIDTH - previousLevelButton_Width - nextLevelButton_Width - 2, 0, previousLevelButton_Width, 60};
    buttonRect[previousLevelButton_MouseIn] = {SCREEN_WIDTH - previousLevelButton_Width - nextLevelButton_Width - 2, 0, previousLevelButton_Width, 60};
    buttonRect[nextLevelButton] = {SCREEN_WIDTH - nextLevelButton_Width - 1, 0, nextLevelButton_Width, 60};
    buttonRect[nextLevelButton_MouseIn] = {SCREEN_WIDTH - nextLevelButton_Width - 1, 0, nextLevelButton_Width, 60};
}

void button::renderButton(SDL_Renderer* renderer)
{
    for (int i = 0; i < 4; i++)
    {
        buttonTexture[i].render (renderer, buttonRect[i].x, buttonRect[i].y);
    }
}

void button::loadButton (SDL_Renderer* renderer)
{
    // load button image
    buttonTexture[restartButton].loadFromFile (renderer, "images/restart.png");
    buttonTexture[restartButton_MouseIn].loadFromFile (renderer, "images/restart_mouse_in.png");

    buttonTexture[nextLevelButton].loadFromFile (renderer, "images/next_level.png");
    buttonTexture[nextLevelButton_MouseIn].loadFromFile (renderer, "images/next_level_mouse_in.png");

    buttonTexture[previousLevelButton].loadFromFile (renderer, "images/previous_level.png");
    buttonTexture[previousLevelButton_MouseIn].loadFromFile (renderer, "images/previous_level_mouse_in.png");

    buttonTexture[undoButton].loadFromFile (renderer, "images/undo.png");
    buttonTexture[undoButton_MouseIn].loadFromFile (renderer, "images/undo_mouse_in.png");
}
void button::checkMouseIn ()
{
    int x, y;
    SDL_GetMouseState (&x, &y);
    mouseRect = {x, y, 1, 1};
    mouseIn = false;
    for (int i = 0; i < 4; i++)
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
void button::handleButton(Map& gameMap, bool& quit, int& level)
{
    switch (currentButton)
    {
    case restartButton:
    {
        quit = true;
        gameMap.resetMapData();
        break;
    }
    case undoButton:
    {
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

