#ifndef buttonClass
#define buttonClass
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <fstream>
#include "LTexture.h"
#include "Map.h"
#include "Person.h"
#include "box.h"
#include "menu.h"
enum buttonType
{
    backToMenuButton,
    restartButton,
    nextLevelButton,
    previousLevelButton,
    undoButton,
    totalButton_mouseOut,
    backToMenuButton_mouseIn = totalButton_mouseOut,
    restartButton_MouseIn,
    nextLevelButton_MouseIn,
    previousLevelButton_MouseIn,
    undoButton_MouseIn,
    totalButton
};
class button:public LTexture
{
	public:
		//Initializes internal variables
		LButton();

		//Sets top left position
		void setPosition(int SCREEN_WIDTH, int SCREEN_HEIGHT);

		//Shows button
		void renderButton(SDL_Renderer* renderer);

        // load button texture
        void loadButton(SDL_Renderer* renderer);
        bool isClicked = false;

        void handleMouseIn (SDL_Renderer* renderer, SDL_Event& e);
        void handleButton (Map& gameMap, bool& quit, int& level, menu& Menu);
        void checkMouseIn ();

        bool mouseIn;
        int currentButton, last = 0;
		SDL_Rect mouseRect;
		SDL_Rect buttonRect [totalButton];
		LTexture buttonTexture[totalButton];

};
#endif // buttonClass
