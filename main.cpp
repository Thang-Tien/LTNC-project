#include "Params.h"
#include "LTexture.h"
#include "Person.h"
#include "Map.h"
#include "box.h"
#include "wall.h"
using std::cout;

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 700;

// khai bao
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;
SDL_Rect movingPerson[4][2];
SDL_Rect standingPerson[4];
Mix_Chunk* boxSlidingSound;
Mix_Chunk* themeMusic;
Person person;
Map gameMap;
box Box;
wall Wall;

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
            }
        }
    }
    return success;
}

bool loadMedia()
{
    bool success = true;
    if (!person.loadFromFile (renderer, "player.png"))
    {
        cout << "Failed to load person texture, Error: " << SDL_GetError() << '\n';
        success = false;
    }
    else
    {
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
            y = 0;
            for (int i=0; i<4; i++)
            {
                standingPerson[i] = {50, y, 50, 50};
                y += 50;
            }
            themeMusic = Mix_LoadWAV ("theme-music.mp3");
            if (themeMusic == NULL)
            {
                cout << "Failed to load theme music, Error: " << SDL_GetError() << '\n';
            }
            boxSlidingSound = Mix_LoadWAV ("box-sliding-sound-effect.wav");
            if (boxSlidingSound == NULL)
            {
                cout << "Failed to load box sliding sound, Erorr: " << SDL_GetError() << '\n';
            }
            gameMap.loadMapData (renderer, "levels/1.txt");
            Box.loadBoxData (gameMap);
            Box.loadBoxTexture (renderer);
            Wall.loadWallData (gameMap);
            Wall.loadWallTexture (renderer);
    }

    return success;
}

void close()
{
    person.free();

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

//void handleEvent ()
int main(int argc, char* args[])
{
    if (!init())
    {
        cout << "Failed to initialize" << '\n';
    }
    else
    {
        if (!loadMedia())
        {
            cout << "Failed to load media" << '\n';
        }
        else
        {
            bool quit = false;
            SDL_Event e;
            person.setPosX (gameMap.XpersonPosition);
            person.setPosY (gameMap.YpersonPosition);
            SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
            SDL_RenderClear (renderer);

            // left feet or right feet
            //          v
            int      left = 0, direction = 0, xPerson = person.getPosX(), yPerson = person.getPosY();

            SDL_Rect personRect, currentClip;
            personRect = {xPerson, yPerson, 50, 50};
            // play theme music
            Mix_PlayChannel (-1, themeMusic, -1);
            while (!quit)
            {
                if (Box.winCheck() == true)
                {
                    cout << "you win" ; quit = true;
                    SDL_Delay (1000);
                }
                gameMap.renderMap (renderer);
                Box.renderBox (renderer);
                Wall.renderWall (renderer);
                while (SDL_PollEvent (&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    else if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
                    {
                        person.setVelX (0);
                        person.setVelY (0);
                        person.distance = 0;
                        person.handleEvent ( direction, left, e);
                        while (person.distance < 50)
                        {
                            // switch feet
                            if (person.distance % 10 == 0)
                            {
                                if (left == 1) left = 0;
                                else left = 1;
                            }

                            currentClip = movingPerson[direction][left];
                            person.moveAndCheckCollision (personRect, Box.boxRect, Box.boxCount, Wall.wallRect, Wall.wallCount);
                            SDL_RenderClear(renderer);
                            //render
                            gameMap.renderMap (renderer);
                            Box.renderBox (renderer);
                            Wall.renderWall (renderer);
                            person.renderPerson(renderer, currentClip);
                            SDL_RenderPresent (renderer);

                            person.distance++;
                            SDL_Delay (5);
                        }
                    }
                }
                currentClip = standingPerson [direction];
                person.renderPerson(renderer, currentClip);
                SDL_RenderPresent(renderer);
            }
        }
    }
    close();
    return 0;
}

