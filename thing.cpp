#include "location.h"
#include "colour.h"
#include "area.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include "button.h"
#include "window.h"
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error: %s \n", SDL_GetError());
    }
    char windowname[18] = "Drawence Dellalio";
    CanvasWindow mainWindow = *new CanvasWindow(windowname, 25, size(atoi(argv[1]), atoi(argv[2])));

    mainWindow.Activate();


    SDL_Quit();
    return 0;
}