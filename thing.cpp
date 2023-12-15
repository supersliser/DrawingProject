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
#include "log.h"

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
    char *inputFile = "NULL";
    char *outputFile = "NULL";

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-x") && windowSize.width == 800)
        {
            windowSize.width = atoi(argv[i + 1]);
        }
        else if (!strcmp(argv[i], "-y") && windowSize.height == 800)
        {
            windowSize.height = atoi(argv[i + 1]);
        }
        else if (strcmp(argv[i], "-i") == 0)
        {
            inputFile = argv[i + 1];
        }
        else if (!strcmp(argv[i], "-o"))
        {
            outputFile = argv[i + 1];
        }
        else if (!strcmp(argv[i], "-useImageSize"))
        {
            windowSize = size(0, 0);
        }
    }
    if (!strcmp(outputFile, "NULL"))
    {
        outputFile = inputFile;
    }
    if (!strcmp(outputFile, "NULL"))
    {
        err("Output path unset. Please provide either an output path or an input path to overwrite.");
        return 1;
    }

    if (strcmp(inputFile, "NULL"))
    {
        CanvasWindow mainWindow = *new CanvasWindow(windowname, 25, windowSize, inputFile, outputFile);
        mainWindow.Activate();
        IMG_Quit();
    }
    else
    {
        CanvasWindow mainWindow = *new CanvasWindow(windowname, 25, windowSize, outputFile);
        mainWindow.Activate();
    }

    SDL_Quit();
    return 0;
}