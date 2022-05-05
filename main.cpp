#include "Params.h"
#include "LTexture.h"
#include "Person.h"
#include "Map.h"
#include "box.h"
#include "wall.h"
#include "button.h"

using std::cout;
using std::to_string;
const int SCREEN_WIDTH = 850;
const int SCREEN_HEIGHT = 700;

// khai bao
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

TTF_Font* font = NULL;
LTexture textTexture;
SDL_Rect movingPerson[4][2];
SDL_Rect standingPerson[4];
int direction = 0;
Mix_Chunk* boxSlidingSound;
Mix_Chunk* themeMusic;

Person person;
Map gameMap;
box Box;
wall Wall;
button Button[totalButton];
SDL_Rect personRect, currentClip;
SDL_Rect buttonRect [totalButton];
SDL_Rect mouseRect;
// khoi tao
bool init()
{
    bool success = true;
    if (SDL_Init (SDL_INIT_EVERYTHING) < 0)
    {
        cout << "SDL could not initialize, Error: " << SDL_GetError() << '\n';
        success = false;
    }
    else
    {
        if (!SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, "linear"))
        {
            cout << "Linear texture filtering not enable!" << '\n';
        }
        window = SDL_CreateWindow ("Pro Render", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            cout << "Unable to create window, Error: " << SDL_GetError() << '\n';
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL)
            {
                cout << "Unable to create renderer, Error: " << SDL_GetError() << '\n';
            }
            else
            {
                SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
                int imgFlags = IMG_INIT_PNG;
                if ( !(IMG_Init (imgFlags) & imgFlags))
                {
                    cout << "SDL_Image could not initialize, Error: " << SDL_GetError();
                    success = false;
                }
                else
                {
                    if( TTF_Init() == -1 )
                    {
                        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                        success = false;
                    }
                }
                if (Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
                {
                    cout << "Unable to initialize mixer, Error: " << SDL_GetError() << '\n';
                    success = false;
                }
                else
                {
                    int restartButton_Width = 60, undoButton_Width = 60,
                        previousLevelButton_Width =  107,
                        nextLevelButton_Width =  107;
                    Button[restartButton].setPosition (SCREEN_WIDTH - restartButton_Width - undoButton_Width - previousLevelButton_Width - nextLevelButton_Width, 0);
                    Button[undoButton].setPosition (SCREEN_WIDTH - undoButton_Width - previousLevelButton_Width - nextLevelButton_Width, 0);
                    Button[previousLevelButton].setPosition (SCREEN_WIDTH - previousLevelButton_Width - nextLevelButton_Width, 0);
                    Button[nextLevelButton].setPosition (SCREEN_WIDTH - nextLevelButton_Width, 0);
                    buttonRect[restartButton] = {Button[restartButton].buttonPosition.x, Button[restartButton].buttonPosition.y, 60, 60};
                    buttonRect[undoButton] = {Button[undoButton].buttonPosition.x, Button[undoButton].buttonPosition.y, 60, 60};
                    buttonRect[previousLevelButton] = {Button[previousLevelButton].buttonPosition.x, Button[previousLevelButton].buttonPosition.y, 107, 60};
                    buttonRect[nextLevelButton] = {Button[nextLevelButton].buttonPosition.x, Button[nextLevelButton].buttonPosition.y, 107, 60};
                }
            }
        }
    }
    return success;
}

bool loadMedia(int level)
{
    bool success = true;
    if (!person.loadFromFile (renderer, "images/player.png"))
    {
        cout << "Failed to load person texture, Error: " << SDL_GetError() << '\n';
        success = false;
    }
    else
    {
        // load moving person
        int y = 0;
        for (int i=0; i<4; i++)
        {
            int x = 0;
            for (int j=0; j<2; j++)
            {
                movingPerson[i][j] = {x, y, 50, 50};
                x += 100;
            }
            y += 50;
        }
        // load standing person
        y = 0;
        for (int i=0; i<4; i++)
        {
            standingPerson[i] = {50, y, 50, 50};
            y += 50;
        }
        // load theme music
        themeMusic = Mix_LoadWAV ("theme-music(2).mp3");
        if (themeMusic == NULL)
        {
            cout << "Failed to load theme music, Error: " << SDL_GetError() << '\n';
            success = false;
        }
        else
        {
            // load map data
            gameMap.loadMapData (renderer, "levels/" + to_string(level) + ".txt");
            Box.loadBoxData (gameMap);
            Box.loadBoxTexture (renderer);
            Wall.loadWallData (gameMap);
            Wall.loadWallTexture (renderer);

            //Open the font
            font = TTF_OpenFont( "AovelSansRounded-rdDL.ttf", 50 );
            if( font == NULL )
            {
                cout << " Failed to load font, Error: " << TTF_GetError() << '\n';
                success = false;
            }
            else
            {
                //Render level text
                SDL_Color textColor = { 0, 0, 0 };
                if( !textTexture.loadFromRenderedText(renderer, font, "Level: " + to_string(level), textColor ) )
                {
                    cout << "Failed to load text texture, Error: " << TTF_GetError() << '\n';
                    success = false;
                }
                else
                {
                    Button[restartButton].loadButton (renderer, "images/restart.png");
                    Button[nextLevelButton].loadButton (renderer, "images/next_level.png");
                    Button[previousLevelButton].loadButton (renderer, "images/previous_level.png");
                    Button[undoButton].loadButton (renderer, "images/undo.png");
                }
            }
        }
    }
    return success;
}

void close()
{
    person.free();
    gameMap.free();
    Wall.free();
    Box.free();
    Mix_FreeChunk (themeMusic);
    themeMusic = NULL;

    SDL_DestroyRenderer (renderer);
    SDL_DestroyWindow (window);
    window = NULL;
    renderer = NULL;

    Mix_Quit();
    SDL_Quit();
    IMG_Quit();
    exit(1);
}

void renderEverything()
{
    gameMap.renderMap (renderer);
    Box.renderBox (renderer);
    Wall.renderWall (renderer);
    textTexture.render(renderer, 0, 0);
    person.renderPerson(renderer, currentClip);
    for (int i = 0; i < totalButton; i++)
    {
        Button[i].renderButton(renderer);
    }
    SDL_RenderPresent(renderer);
}
int main(int argc, char* args[])
{
    if (!init())
    {
        cout << "Failed to initialize" << '\n';
    }
    else
    {
        bool quitGame = false, isPlayingMusic = false;
        int level = 0, x, y;
        while (level <= 107 && !quitGame)
        {

            if (!loadMedia(level))
            {
                cout << "Failed to load media" << '\n';
            }
            else
            {
                person.setPosX (gameMap.XpersonPosition);
                person.setPosY (gameMap.YpersonPosition);
                bool quit = false, mouseIn = false;
                SDL_Event e;
                SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
                SDL_RenderClear (renderer);

                // left feet or right feet
                //          v
                int      left = 0, currentButton;
                // set person initial position
                personRect = {person.getPosX(), person.getPosY(), 50, 50};
                // play theme music
                if (!isPlayingMusic)
                {
                    Mix_PlayChannel (-1, themeMusic, -1);
                    isPlayingMusic = true;
                }
                while (!quit)
                {
                    currentClip = standingPerson [direction];

                    // render
                    renderEverything();

                    // get mouse position
                    SDL_GetMouseState (&x, &y);
                    mouseRect = {x, y, 1, 1};
                    mouseIn = false;

                    person.goHorizontal = false;
                    person.goVertical = false;
                    for (int i = 0; i < totalButton; i++)
                    {
                            if (Button[i].checkCollision (mouseRect, buttonRect[i]) == true)
                            {
                                currentButton = i;
                                mouseIn = true;
                                break;
                            }
                    }
                    while (SDL_PollEvent (&e) != 0)
                    {
                        if (e.type == SDL_QUIT)
                        {
                            quit = true;
                            quitGame = true;
                        }
                        // check if mouse is in the button
                        else if (e.type == SDL_MOUSEBUTTONDOWN)
                        {

                            if (mouseIn == true)
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
                                        if (level < 0) {level = 0;}
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
                        }

                        else if ((e.type == SDL_KEYDOWN && e.key.repeat == 0) &&
                                 (e.key.keysym.sym == SDLK_UP ||
                                  e.key.keysym.sym == SDLK_DOWN ||
                                  e.key.keysym.sym == SDLK_LEFT ||
                                  e.key.keysym.sym == SDLK_RIGHT))
                        {
                            person.setVelX (0);
                            person.setVelY (0);
                            person.distance = 0;
                            person.handleEvent ( direction, left, e);
                            // moving animation
                            while (person.distance < 50)
                            {
                                // switch feet
                                if (person.distance % 10 == 0)
                                {
                                    if (left == 1) left = 0;
                                    else left = 1;
                                }
                                currentClip = movingPerson[direction][left];
                                person.moveAndCheckCollision (renderer, personRect, Box.boxRect, Box.boxCount, Wall.wallRect, Wall.wallCount);

                                // clear existed screen
                                SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
                                SDL_RenderClear(renderer);

                                // render while person is running
                                renderEverything();

                                // update distance
                                person.distance++;
                                SDL_Delay (5);
                            }

                        }
                    }
                    if (Box.winCheck() == true)
                    {
                        cout << "you win" << '\n' ;
                        quit = true;
                        gameMap.resetMapData();
                        level ++;
                    }

                }
            }
        }
    }
    close();
    return 0;
}

