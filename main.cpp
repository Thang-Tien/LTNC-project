#include "Params.h"
#include "LTexture.h"
#include "Person.h"
#include "Map.h"
#include "box.h"
#include "wall.h"
#include "button.h"
#include "score.h"
#include "menu.h"
#include "music.h"
using std::cout;
using std::to_string;
const int SCREEN_WIDTH = 850;
const int SCREEN_HEIGHT = 700;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

TTF_Font* font = NULL;
LTexture textTexture;
LTexture background;
SDL_Rect movingPerson[4][2];
SDL_Rect standingPerson[4];
int direction = 0;

Person person;
Map gameMap;
box Box;
wall Wall;
score Score;
button Button;
menu Menu;
music Music;
SDL_Rect personRect, currentClip;
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

                // load person image
                if (!person.loadFromFile (renderer, "images/player.png"))
                {
                    cout << "Failed to load person texture, Error: " << SDL_GetError() << '\n';
                    success = false;
                }

                // load music
                Music.loadMusic ();

                // load grass, floor, goal, box and wall texture
                gameMap.grass.loadFromFile (renderer, "images/grass.png");
                gameMap.floor.loadFromFile (renderer, "images/floor.png");
                gameMap.goal.loadFromFile (renderer, "images/goal.png");
                Box.loadBoxTexture (renderer);
                Wall.loadWallTexture (renderer);

                // load ttf font for rendering score
                Score.scoreFont = TTF_OpenFont("AovelSansRounded-rdDL.ttf", 30);

                // load ttf font for render level numbers
                Menu.levelNumFont = TTF_OpenFont ("04B_09__.ttf", 20);

                Menu.loadLevelNum (renderer);

                // load menu button
                Menu.loadMenuButton (renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

                // load button texture
                Button.loadButton(renderer);

                // set button position
                Button.setPosition(SCREEN_WIDTH, SCREEN_HEIGHT);

                // load moving person rect
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
            }
        }
    }
    return success;
}

bool loadMedia(int level)
{
    bool success = true;

    // load map data
    gameMap.loadMapData (renderer, "levels/" + to_string(level) + ".txt");

    Box.loadBoxData (gameMap);
    Wall.loadWallData (gameMap);

    //Open the font
    font = TTF_OpenFont( "AovelSansRounded-rdDL.ttf", 50 );
    if( font == NULL )
    {
        cout << " Failed to load font, Error: " << TTF_GetError() << '\n';
        success = false;
    }

    //Render level text
    SDL_Color textColor = { 0, 0, 0 };
    if( !textTexture.loadFromRenderedText(renderer, font, "Level: " + to_string(level), textColor ) )
    {
        cout << "Failed to load text texture, Error: " << TTF_GetError() << '\n';
        success = false;
    }
    // load score from file
    Score.loadTTFScore (renderer);
    Score.loadBestScore("scores/" + to_string(level) + ".txt");
    return success;
}

void close()
{
    person.free();
    gameMap.free();
    Wall.free();
    Box.free();
    Mix_FreeMusic (Music.themeMusic);
    Music.themeMusic = NULL;

    SDL_DestroyRenderer (renderer);
    SDL_DestroyWindow (window);
    window = NULL;
    renderer = NULL;

    Mix_Quit();
    SDL_Quit();
    IMG_Quit();
    exit(1);
}

void renderEverything(SDL_Event& e)
{
    SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
    SDL_RenderClear (renderer);
    background.render (renderer, 0, 0);
    gameMap.renderMap (renderer);

    Box.renderBox (renderer);
    Wall.renderWall (renderer);
    textTexture.render(renderer, 0, 0);
    person.renderPerson(renderer, currentClip);
    Button.renderButton(renderer);
    Button.checkMouseIn();

    // mouse in button animation effect
    if (Button.mouseIn == true)
    {
        Button.handleMouseIn(renderer, e);
    }

    Score.renderScore(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
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
        int level = 0;
        SDL_Event menuEvent;
        while (level <= 105)
        {
            // play theme music
            if (!isPlayingMusic)
            {
                Mix_PlayMusic (Music.themeMusic, -1);
                isPlayingMusic = true;
            }

            // main menu
            while (Menu.mainMenu)
            {
                Menu.checkLevelWon ();
                while (Menu.atMainMenu)
                {
                    Menu.renderMainMenu (renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
                    Menu.handleMainMenu (menuEvent, renderer, quitGame);
                    SDL_RenderPresent (renderer);
                    SDL_Delay(5);
                }

                while (Menu.choosingLevel)
                {
                    Menu.mainMenuBackGround.render (renderer, 0, 0);
                    Menu.backButton.render (renderer, 0, 0);

                    Menu.renderLevelList (renderer);
                    Menu.handleLevelList (menuEvent, renderer, level, quitGame);

                    SDL_RenderPresent (renderer);
                    SDL_Delay(5);
                }
                while (Menu.tutorial)
                {
                    Menu.tutorialTexture.render(renderer, 0, 0);
                    Menu.backButton.render (renderer, 0, 0);

                    Menu.handleTutorial (menuEvent, renderer, quitGame);

                    SDL_RenderPresent (renderer);
                }
                while (Menu.credit)
                {
                    Menu.creditTexture.render(renderer, 0, 0);
                    Menu.backButton.render (renderer, 0, 0);

                    Menu.handleCredit (menuEvent, renderer, quitGame);

                    SDL_RenderPresent (renderer);
                }
            }

            if (quitGame == true) break;
            else if (!loadMedia(level))
            {
                cout << "Failed to load media" << '\n';
                quitGame = true;

            }
            else
            {
                // set person's initial position
                person.setPosX (gameMap.XpersonPosition);
                person.setPosY (gameMap.YpersonPosition);

                // save person's first posisiton
                person.lastPosX.push_back (gameMap.XpersonPosition);
                person.lastPosY.push_back (gameMap.YpersonPosition);

                // save boxes's first position
                Box.saveLastBoxesPos ();

                Score.currentSteps = 0;
                direction = 0;
                Score.currentTime = 0;

                bool quit = false;
                SDL_Event e;
                SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
                SDL_RenderClear (renderer);

                // left feet or right feet
                //         v
                int      left = 0;

                personRect = {person.getPosX(), person.getPosY(), 50, 50};

                // set start time
                Score.startTime = SDL_GetTicks();

                // game loop
                while (!quit)
                {
                    Score.currentTime = (SDL_GetTicks() - Score.startTime)/1000;
                    Score.loadTTFScore (renderer);
                    currentClip = standingPerson [direction];

                    // render
                    renderEverything(e);

                    person.goHorizontal = false;
                    person.goVertical = false;

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
                            if (Button.mouseIn == true)
                            {
                                Button.handleButton(gameMap, quit, level, Menu);
                                if (Button.currentButton == undoButton)
                                {
                                    // undo
                                    if (Button.last > person.lastPosX.size ())
                                    {
                                        Button.last  = person.lastPosX.size ();
                                    }
                                    person.setPosX (person.lastPosX [person.lastPosX.size () - Button.last]);
                                    person.setPosY (person.lastPosY [person.lastPosY.size () - Button.last]);
                                    Score.currentSteps --;
                                    if (Score.currentSteps < 0) Score.currentSteps = 0;
                                    Box.backLastPos (Button.last);
                                }
                                if (Button.currentButton == restartButton || Button.currentButton == nextLevelButton || Button.currentButton == previousLevelButton)
                                {
                                    // clear person position data
                                    person.lastPosX.clear();
                                    person.lastPosY.clear();
                                }
                            }
                        }

                        else if ((e.type == SDL_KEYDOWN && e.key.repeat == 0) &&
                                 (e.key.keysym.sym == SDLK_UP ||
                                  e.key.keysym.sym == SDLK_DOWN ||
                                  e.key.keysym.sym == SDLK_LEFT ||
                                  e.key.keysym.sym == SDLK_RIGHT))
                        {
                            // save boxes's previous position
                            Box.saveLastBoxesPos ();

                            person.setVelX (0);
                            person.setVelY (0);
                            person.distance = 0;
                            person.handleEvent ( direction, left, e);

                            // check if person has moved or not
                            person.previousPosX = person.getPosX();
                            person.previousPosY = person.getPosY();

                            // save person's previous position to vector
                            person.lastPosX.push_back (person.getPosX());
                            person.lastPosY.push_back (person.getPosY());

                            // number of steps we want to undo
                            Button.last = 0;

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

                                Score.currentTime = (SDL_GetTicks() - Score.startTime)/1000;
                                Score.loadTTFScore (renderer);
                                // render while person is running
                                renderEverything(e);

                                // update distance
                                person.distance++;
                                SDL_Delay (5);
                            }
                            if (person.previousPosX != person.getPosX() || person.previousPosY != person.getPosY())
                                Score.currentSteps ++;
                        }

                    }
                    // check if win or not
                    if (Box.winCheck() == true)
                    {
                        // update best steps
                        if (Score.bestSteps == 0) Score.bestSteps = Score.currentSteps;
                        else if (Score.bestSteps != 0 && Score.currentSteps < Score.bestSteps)
                        {
                            Score.bestSteps = Score.currentSteps;
                        }

                        if (Score.bestTime == 0) Score.bestTime = Score.currentTime;

                        // update best time
                        else if (Score.bestTime != 0 && Score.currentTime < Score.bestTime)
                        {
                            Score.bestTime = Score.currentTime;
                        }
                        // reset last box list
                        Box.totalLastBox = 0;

                        // save score to file
                        Score.saveScore ("scores/" + to_string(level) + ".txt");

                        direction = 0;
                        quit = true;
                        gameMap.resetMapData();
                        level ++;
                    }
                    SDL_Delay (5);
                }
            }
        }
    }
    close();
    return 0;
}
