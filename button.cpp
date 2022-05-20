#include "button.h"

button::LButton()
{
    mouseIn = false;
}

void button::setPosition(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    buttonRect[muteButton] = {SCREEN_WIDTH - buttonTexture[backToMenuButton].getWidth()- buttonTexture[restartButton].getWidth() - buttonTexture[undoButton].getWidth() - buttonTexture[previousLevelButton].getWidth()
                              - buttonTexture[nextLevelButton].getWidth() - buttonTexture[backToMenuButton].getWidth(),
                              0, buttonTexture[muteButton].getWidth(), buttonTexture[muteButton].getHeight()};

    buttonRect[unMuteButton] = buttonRect[muteButton];
    buttonRect[muteButton_mouseIn] = buttonRect[muteButton];
    buttonRect[unMuteButton_mouseIn] = buttonRect[muteButton];

    buttonRect[backToMenuButton] = {SCREEN_WIDTH - buttonTexture[restartButton].getWidth() - buttonTexture[undoButton].getWidth() - buttonTexture[previousLevelButton].getWidth()
                                    - buttonTexture[nextLevelButton].getWidth() - buttonTexture[backToMenuButton].getWidth(),
                                    0, buttonTexture[backToMenuButton].getWidth(), buttonTexture[backToMenuButton].getHeight()};

    buttonRect[backToMenuButton_mouseIn] = buttonRect[backToMenuButton];

    buttonRect[restartButton] = {SCREEN_WIDTH - buttonTexture[restartButton].getWidth() - buttonTexture[undoButton].getWidth()
                                 - buttonTexture[previousLevelButton].getWidth() - buttonTexture[nextLevelButton].getWidth(),
                                 0, buttonTexture[restartButton].getWidth (), buttonTexture[restartButton].getHeight()};

    buttonRect[restartButton_mouseIn] = buttonRect[restartButton];

    buttonRect[undoButton] = {SCREEN_WIDTH - buttonTexture[undoButton].getWidth()
                              - buttonTexture[previousLevelButton].getWidth() - buttonTexture[nextLevelButton].getWidth(),
                              0, buttonTexture[undoButton].getWidth(), buttonTexture[undoButton].getHeight()};

    buttonRect[undoButton_mouseIn] = buttonRect[undoButton];

    buttonRect[previousLevelButton] = {SCREEN_WIDTH - buttonTexture[previousLevelButton].getWidth()
                                       - buttonTexture[nextLevelButton].getWidth(),
                                       0, buttonTexture[previousLevelButton].getWidth(), buttonTexture[previousLevelButton].getHeight()};

    buttonRect[previousLevelButton_mouseIn] = buttonRect[previousLevelButton];

    buttonRect[nextLevelButton] = {SCREEN_WIDTH - buttonTexture[nextLevelButton].getWidth(),
                                   0, buttonTexture[nextLevelButton].getWidth(), buttonTexture[nextLevelButton].getHeight()};

    buttonRect[nextLevelButton_mouseIn] = buttonRect[nextLevelButton];
}

void button::renderButton(SDL_Renderer* renderer)
{
    for (int i = 0; i < totalButton_MouseOut; i++)
    {
        buttonTexture[i].render (renderer, buttonRect[i].x, buttonRect[i].y);
    }
    //If the music is paused
    if( Mix_PausedMusic() == 1 )
    {
        buttonTexture[muteButton].render (renderer, buttonRect[muteButton_mouseIn].x, buttonRect[muteButton_mouseIn].y);
    }
    //If the music is playing
    else
    {
        buttonTexture[unMuteButton].render (renderer, buttonRect[muteButton_mouseIn].x, buttonRect[muteButton_mouseIn].y);
    }
}

void button::loadButton (SDL_Renderer* renderer)
{
    buttonTexture[muteButton].loadFromFile (renderer, "buttons/CasualIcons_Locked_020.png");
    buttonTexture[muteButton_mouseIn].loadFromFile (renderer, "buttons/CasualIcons_020.png");
    buttonTexture[unMuteButton].loadFromFile (renderer, "buttons/CasualIcons_Locked_018.png");
    buttonTexture[unMuteButton_mouseIn].loadFromFile (renderer, "buttons/CasualIcons_018.png");

    buttonTexture[backToMenuButton].loadFromFile (renderer, "buttons/CasualIcons_Locked_006.png");
    buttonTexture[backToMenuButton_mouseIn].loadFromFile (renderer, "buttons/CasualIcons_006.png");

    buttonTexture[restartButton].loadFromFile (renderer, "buttons/CasualIcons_Locked_004.png");
    buttonTexture[restartButton_mouseIn].loadFromFile (renderer, "buttons/CasualIcons_004.png");

    buttonTexture[nextLevelButton].loadFromFile (renderer, "buttons/CasualIcons_Locked_025.png");
    buttonTexture[nextLevelButton_mouseIn].loadFromFile (renderer, "buttons/CasualIcons_025.png");

    buttonTexture[previousLevelButton].loadFromFile (renderer, "buttons/CasualIcons_Locked_026.png");
    buttonTexture[previousLevelButton_mouseIn].loadFromFile (renderer, "buttons/CasualIcons_026.png");

    buttonTexture[undoButton].loadFromFile (renderer, "buttons/CasualIcons_Locked_023.png");
    buttonTexture[undoButton_mouseIn].loadFromFile (renderer, "buttons/CasualIcons_023.png");
}
void button::checkMouseIn ()
{
    int x, y;
    SDL_GetMouseState (&x, &y);
    mouseRect = {x, y, 1, 1};
    mouseIn = false;
    for (int i = 0; i < totalButton_MouseOut; i++)
    {
        if (checkCollision (mouseRect, buttonRect[i]) == true)
        {
            currentButton = i;
            mouseIn = true;
        }
    }
}

void button::handleMouseIn(SDL_Renderer* renderer, SDL_Event& e)
{

    switch (currentButton)
    {
    case unMuteButton:
    {
        //If the music is paused
        if( Mix_PausedMusic() == 1 )
        {
            buttonTexture[muteButton_mouseIn].render (renderer, buttonRect[muteButton_mouseIn].x, buttonRect[muteButton_mouseIn].y);
        }
        //If the music is playing
        else
        {
            buttonTexture[unMuteButton_mouseIn].render (renderer, buttonRect[muteButton_mouseIn].x, buttonRect[muteButton_mouseIn].y);
        }
        break;
    }
    case backToMenuButton:
    {
        buttonTexture[backToMenuButton_mouseIn].render (renderer, buttonRect[backToMenuButton_mouseIn].x, buttonRect[backToMenuButton_mouseIn].y);
        break;
    }
    case restartButton:
    {
        buttonTexture[restartButton_mouseIn].render (renderer, buttonRect[restartButton_mouseIn].x, buttonRect[restartButton_mouseIn].y);
        break;
    }
    case undoButton:
    {
        buttonTexture[undoButton_mouseIn].render (renderer, buttonRect[undoButton_mouseIn].x, buttonRect[undoButton_mouseIn].y);
        break;
    }
    case previousLevelButton:
    {
        buttonTexture[previousLevelButton_mouseIn].render (renderer, buttonRect[previousLevelButton_mouseIn].x, buttonRect[previousLevelButton_mouseIn].y);
        break;
    }
    case nextLevelButton:
    {
        buttonTexture[nextLevelButton_mouseIn].render (renderer, buttonRect[nextLevelButton_mouseIn].x, buttonRect[nextLevelButton_mouseIn].y);
        break;
    }
    }

}
void button::handleButton(Map& gameMap, bool& quit, int& level, menu& Menu)
{
    switch (currentButton)
    {
    case unMuteButton:
    {
        //If the music is paused
        if( Mix_PausedMusic() == 1 )
        {
            //Resume the music
            Mix_ResumeMusic();
        }
        //If the music is playing
        else
        {
            //Pause the music
            Mix_PauseMusic();
        }
        break;
    }
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
