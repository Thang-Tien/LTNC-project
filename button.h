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
enum buttonType
{
    restartButton,
    nextLevelButton,
    previousLevelButton,
    undoButton,
    totalButton
};
class button:public LTexture
{
	public:
		//Initializes internal variables
		LButton();
		//Sets top left position
		void setPosition( int x, int y );
		//Shows button
		void renderButton(SDL_Renderer* renderer);
        // load button texture
        void loadButton(SDL_Renderer* renderer, string path);

        bool isClicked = false;
		//Top left position
		SDL_Point buttonPosition;
		LTexture buttonTexture;

};
#endif // buttonClass
