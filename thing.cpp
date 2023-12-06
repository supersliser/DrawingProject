#include "location.h"
#include "colour.h"
#include "area.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include "button.h"
#include "window.h"

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error: %s \n", SDL_GetError());
    }
    CanvasWindow* mainWindow = new CanvasWindow("Drawence Dellalio");

    (*mainWindow).Draw();

    bool drawing = 0;
    bool finished = 0;

    (*mainWindow).Activate();
    delete mainWindow;
    SDL_Quit();
    return 0;
}