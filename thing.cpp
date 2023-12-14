#include "location.h"
#include "colour.h"
#include "area.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include "button.h"
#include "window.h"
#include <stdlib.h>
#include <ctype.h>
#include <SDL2/SDL_image.h>

bool checkStringIsNum(char *in)
{
    for (int i = 0; i < sizeof(in) / sizeof(char); i++)
    {
        if (!isdigit(*(in + i)))
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error: %s \n", SDL_GetError());
    }
    char windowname[18] = "Drawence Dellalio";
    size windowSize = size(800, 800);
    char *inputFile;

    if (argc == 3)
    {
        if (!checkStringIsNum(argv[1]) || !checkStringIsNum(argv[2]))
        {
            windowSize = size(atoi(argv[1]), atoi(argv[2]));
        }
    }
    else if (argc == 2)
    {
        inputFile = argv[1];
        IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF|IMG_INIT_WEBP);
    }
    else if (argc == 4)
    {
        if (!checkStringIsNum(argv[1]) || !checkStringIsNum(argv[2]))
        {
            windowSize = size(atoi(argv[1]), atoi(argv[2]));
        }
        inputFile = argv[3];
        IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF|IMG_INIT_WEBP);
    }
    CanvasWindow mainWindow = *new CanvasWindow(windowname, 25, windowSize);
    mainWindow.Activate();

    if (sizeof(inputFile) > 0)
    {
        IMG_Quit();
    }
    SDL_Quit();
    return 0;
}