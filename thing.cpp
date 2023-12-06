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
    Window* mainWindow = new Window("Drawence Dellalio");

    (*mainWindow).Activate();

    delete mainWindow;
    SDL_Quit();
    return 0;
}