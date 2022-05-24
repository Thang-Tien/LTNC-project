#include "score.h"
using std::ifstream;
using std::ofstream;
using std::cout;
using std::to_string;
score::score()
{
    currentSteps = 0;
    currentTime = 0;
    bestSteps = 0;
    bestTime = 0;
    scoreFont = NULL;
    textColor = { 0, 0, 0 };
}
void score::loadBestScore (string path)
{
    ifstream fi (path.c_str());
    fi >> bestSteps >> bestTime;
}

void score::loadTTFScore(SDL_Renderer* renderer)
{

    if( scoreFont == NULL )
    {
        cout << " Failed to load score scoreFont, Error: " << TTF_GetError() << '\n';
    }

    // load step from file
    cStep.loadFromRenderedText(renderer, scoreFont, "Steps: " + to_string(currentSteps) + " ", textColor);

    if (bestSteps > 0)
    bStep.loadFromRenderedText(renderer, scoreFont, "Best steps: " + to_string(bestSteps) + " ", textColor);

    else bStep.loadFromRenderedText(renderer, scoreFont, "Best steps: -- ", textColor);

    // format current time clock
    string currentTimeClockMin = (currentTime/60 > 9) ? (to_string (currentTime/60)) : ("0" + to_string (currentTime/60)),
           currentTimeClockSec = (currentTime - int(currentTime/60)*60 > 9) ?
           to_string (currentTime - int(currentTime/60)*60) : ("0" + to_string (currentTime - int(currentTime/60)*60));
    cTime.loadFromRenderedText(renderer, scoreFont, "Time: " + currentTimeClockMin + ":" + currentTimeClockSec + " ", textColor);

    // format best time clock
    string bestTimeClockMin = "--", bestTimeClockSec = "--";
    if (bestTime > 0)
    {
        bestTimeClockMin = (bestTime/60 > 9) ? (to_string (bestTime/60)) : ("0" + to_string (bestTime/60));
        bestTimeClockSec = (bestTime - int(bestTime/60)*60 > 9) ?
        to_string (bestTime - int(bestTime/60)*60) : ("0" + to_string (bestTime - int(bestTime/60)*60));
    }
    bTime.loadFromRenderedText(renderer, scoreFont, "Best time: " + bestTimeClockMin + ":" + bestTimeClockSec + " ", textColor);

}

void score::renderScore(SDL_Renderer* renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
    cStep.render (renderer, 0, SCREEN_HEIGHT - cStep.getHeight());
    cTime.render (renderer, cStep.getWidth(), SCREEN_HEIGHT - cTime.getHeight());
    bStep.render (renderer, cStep.getWidth() + cTime.getWidth(), SCREEN_HEIGHT - bStep.getHeight());
    bTime.render (renderer, cStep.getWidth() + cTime.getWidth() + bStep.getWidth(), SCREEN_HEIGHT - bTime.getHeight());
}
void score::saveScore(string path)
{
    ofstream fo (path.c_str());
    fo << bestSteps << " " << bestTime;
}


