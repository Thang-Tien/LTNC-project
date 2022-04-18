#include "Params.h"
#include "LTexture.h"
#include "Person.h"
#include "Params.h"
using std::cout;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;
bool init ();
bool loadMedia();
void close();

// khai bao
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
TTF_Font* font = NULL;
LTexture personTexture;
LTexture boxTexture;
SDL_Rect movingPerson[4][2];
SDL_Rect standingPerson[4];
Mix_Chunk* boxSlidingSound;
Mix_Chunk* themeMusic;

class Person
{
public:
    const int Person_Width = 32;
    const int Person_Height = 32;
    const int Person_Vel = 10;

    Person();
    void handleEvent(int& direction, int& i, SDL_Event& e);
    void move(SDL_Rect& personRect, SDL_Rect& boxRect);
    void render(SDL_Rect& currentClip);
    bool checkCollision(SDL_Rect a, SDL_Rect b);
    int getPosX ();
    int getPosY ();
    int getWidth();
    int getHeight ();
private:
    int posX, posY;
    int velX, velY;
};


Person::Person()
{
    posX = 0;
    posY = 0;

    velX = 0;
    velY = 0;

}

void Person::handleEvent (int& direction, int& left, SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
        {
            velY -= 1;
            direction = 3;
            break;

        }
        case SDLK_DOWN:
        {
            velY += 1;
            direction = 0;
            break;

        }
        case SDLK_LEFT:
        {
            velX -= 1;
            direction = 1;
            break;

        }
        case SDLK_RIGHT:
        {

            velX += 1;
            direction = 2;
            break;
        }
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
        {
            velY += 1;
            direction = 3;
            break;

        }
        case SDLK_DOWN:
        {
            velY -= 1;
            direction = 0;
            break;

        }
        case SDLK_LEFT:
        {
            velX += 1;
            direction = 1;
            break;

        }
        case SDLK_RIGHT:
        {

            velX -= 1;
            direction = 2;
            break;
        }
        }
    }
}

void Person::move(SDL_Rect& personRect, SDL_Rect& boxRect)
{
    posX += velX;
    personRect = {posX, posY, personRect.w, personRect.h};
    boxRect = {boxRect.x, boxRect.y, boxRect.w, boxRect.h};
    if (velX > 0)
    {
        if (checkCollision(personRect, boxRect) == true)
        {
            cout << "Collision detected !!!" << '\n';
            boxRect.x = posX + personRect.w;
            boxRect = {boxRect.x, boxRect.y, boxRect.w, boxRect.h};
        }
    }
    if (velX < 0)
    {
        if (checkCollision(personRect, boxRect) == true)
        {
            cout << "Collision detected !!!" << '\n';
            boxRect.x = posX - boxRect.w;
            boxRect = {boxRect.x, boxRect.y, boxRect.w, boxRect.h};
        }
    }
    posY += velY;
    personRect = {posX, posY, personRect.w, personRect.h};
    if (velY > 0)
    {
        if (checkCollision(personRect, boxRect) == true)
        {
            cout << "Collision detected !!!" << '\n';
            boxRect.y = posY + 32;
            boxRect = {boxRect.x, boxRect.y, boxRect.w, boxRect.h};
        }
    }
    if (velY < 0)
    {
        if (checkCollision(personRect, boxRect) == true)
        {
            cout << "Collision detected !!!" << '\n';
            boxRect.y = posY - boxRect.h;
            boxRect = {boxRect.x, boxRect.y, boxRect.w, boxRect.h};
        }
    }
}

void Person::render (SDL_Rect& currentClip)
{
    personTexture.render (renderer, posX, posY, &currentClip);
}

int Person::getPosX ()
{
    return posX;
}

int Person::getPosY ()
{
    return posY;
}

int Person::getWidth ()
{
    return Person_Width;
}

int Person::getHeight ()
{
    return Person_Height;
}

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
    if (!personTexture.loadFromFile (renderer, "player.png"))
    {
        cout << "Failed to load person texture, Error: " << SDL_GetError() << '\n';
        success = false;
    }
    else
    {
        if (!boxTexture.loadFromFile(renderer, "box.png"))
        {
            cout << "Failed to load box texture, Error: " << SDL_GetError() << '\n';
        }
        else
        {
            int y = 0;
            for (int i=0; i<4; i++)
            {
                int x = 0;
                for (int j=0; j<2; j++)
                {
                    movingPerson[i][j] = {x, y, 32, 32};
                    x += 64;
                }
                y += 32;
            }
            y = 0;
            for (int i=0; i<4; i++)
            {
                standingPerson[i] = {32, y, 32, 32};
                y += 32;
            }
            themeMusic = Mix_LoadWAV ("theme-song.wav");
            if (themeMusic == NULL)
            {
                cout << "Failed to load theme music, Error: " << SDL_GetError() << '\n';
            }
            boxSlidingSound = Mix_LoadWAV ("box-sliding-sound-effect.wav");
            if (boxSlidingSound == NULL)
            {
                cout << "Failed to load box sliding sound, Erorr: " << SDL_GetError() << '\n';
            }

        }

    }

    return success;
}

void close()
{
    personTexture.free();

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

bool Person::checkCollision(SDL_Rect a, SDL_Rect b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
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
            Person Person;
            int left = 0, xBox = SCREEN_WIDTH/2, yBox = SCREEN_HEIGHT/2,
                direction = 0, xPerson = Person.getPosX(), yPerson = Person.getPosY(),
                 Person_Width = Person.getWidth(), Person_Height = Person.getHeight();
            SDL_Rect currentClip, standingClip;
            SDL_Rect personRect, boxRect;
            personRect = {xPerson, yPerson, 32, 32};
            boxRect = {xBox, yBox, boxTexture.getWidth(), boxTexture.getHeight()};
            Mix_PlayChannel (-1, themeMusic, -1);
            while (!quit)
            {
                xPerson = Person.getPosX();
                yPerson = Person.getPosY();
                personRect = {xPerson, yPerson, 32, 32};
                boxRect = {xBox, yBox, boxTexture.getWidth(), boxTexture.getHeight()};
                while (SDL_PollEvent (&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP )
                    {
                        Person.handleEvent ( direction, left, e);
                        if (left == 0)
                        {
                            left = 1;
                        }
                        else left = 0;
                        currentClip = movingPerson[direction][left];
                        if (e.type == SDL_KEYUP)
                        {
                            currentClip = standingPerson [direction];
                        }
                    }
                }

                SDL_RenderClear (renderer);
                Person.move(personRect, boxRect);
                xBox = boxRect.x;
                yBox = boxRect.y;
                Person.render(currentClip);
                boxTexture.render(renderer, xBox, yBox);
                SDL_RenderPresent(renderer);
            }
        }
    }
    close();
    return 0;
}

