#include "location.h"
#include "colour.h"
#include "area.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include "button.h"

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error: %s \n", SDL_GetError());
    }
    int windowWidth = 1200;
    int windowHeight = 600;
    SDL_Window *window = SDL_CreateWindow("testwindow1", 100, 100, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderClear(renderer);
    int finished = 0;
    colour CurrentColour = colour(black);
    ColourButton Colours[10];

    ResizableArea colourArea = *new ResizableArea(location(0), size(windowWidth, 120), colour(60), colour(255), 4, SizeLock::height, window);
    ResizableArea CanvasArea = *new ResizableArea(location(0, 160), size(windowWidth, windowHeight - (colourArea.getSize().height * 2)), colour(128), colour(255), 0, SizeLock::width, window);
    Area canvas = *new Area(location(40, 0), size(CanvasArea.getSize().width - 80, CanvasArea.getSize().height), colour(255), colour(255));
    CanvasArea.addChild(&canvas);

    const int ButtonSize = 25;
    for (int i = 0; i < 8; i++)
    {
        Colours[i] = *new ColourButton(*(new location(colourArea.getPosition().x + 80 + ((int)(i / 2) * ButtonSize), colourArea.getPosition().y + 20 + (ButtonSize * (i % 2)))), size(ButtonSize), colour((defaultColours)i), colour(255));
    }

    SDL_Rect brush;
    brush.w = 5;
    brush.h = 5;

        colourArea.Draw(renderer, window);
        CanvasArea.Draw(renderer, window);
        for (int i = 0; i < 8; i++)
        {
            Colours[i].Draw(renderer);
        }
    char drawing = 0;

    while (!finished)
    {
        SDL_Event event; /* an incoming event */
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                finished = 1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                drawing = 1;
                for (int i = 0; i < 8; i++)
                {
                    if (event.button.x >= Colours[i].getPosition().x && 
                    event.button.x <= Colours[i].getPosition().x + Colours[i].getSize().width && 
                    event.button.y >= Colours[i].getPosition().y && 
                    event.button.y <= Colours[i].getPosition().y + Colours[i].getSize().height)
                    {
                        Colours[i].Click(&CurrentColour);
                        printf("current colour is %d, %d, %d, %d", CurrentColour.r, CurrentColour.g, CurrentColour.b, CurrentColour.a);
                        fflush(stdout);
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                drawing = 0;
                break;
            case SDL_MOUSEMOTION:
                if (event.button.y >= canvas.getPosition().y && event.button.y <= canvas.getPosition().y + canvas.getSize().height && event.button.x >= canvas.getPosition().x && event.button.x <= canvas.getPosition().x + canvas.getSize().width)
                {
                    if (drawing)
                    {
                        SDL_SetRenderDrawColor(renderer, CurrentColour.r, CurrentColour.g, CurrentColour.b, CurrentColour.a);
                        brush.x = event.button.x - 2;
                        brush.y = event.button.y - 2;
                        SDL_RenderFillRect(renderer, &brush);
                    }
                }
                break;
            }
        }

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}