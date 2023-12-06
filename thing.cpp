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
    while (!finished)
    {
        SDL_Event event; /* an incoming event */
        while (SDL_PollEvent(&event))
        {
            if (drawing)
            {
                if (event.button.y >= canvas.getPosition().y && event.button.y <= canvas.getPosition().y + canvas.getSize().height && event.button.x >= canvas.getPosition().x && event.button.x <= canvas.getPosition().x + canvas.getSize().width)
                {
                    SDL_SetRenderDrawColor(renderer, CurrentColour.r, CurrentColour.g, CurrentColour.b, CurrentColour.a);
                    brush.x = event.button.x - 2;
                    brush.y = event.button.y - 2;
                    SDL_RenderFillRect(renderer, &brush);
                }
            }
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
            }
        }

        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}