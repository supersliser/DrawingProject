#include "window.h"
#include "area.h"
#include "log.h"
#include <SDL2/SDL.h>

Window::Window()
{
}
Window::Window(char *WindowName)
{
    CreateWindow(WindowName, location(50, 50), size(800, 800), colour(white), SDL_WINDOW_RESIZABLE);
}
Window::Window(char *WindowName, location Position, size Size)
{
    CreateWindow(WindowName, Position, Size, colour(white), SDL_WINDOW_RESIZABLE);
}
Window::Window(char *WindowName, size Size)
{
    CreateWindow(WindowName, location(50, 50), Size, colour(white), SDL_WINDOW_RESIZABLE);
}
void Window::CreateWindow(char *Name, location Position, size Size, colour InitialColour, Uint32 Flags)
{
    SDL_Window *temp = SDL_CreateWindow(Name, Position.x, Position.y, Size.width, Size.height, Flags);
    window = temp;
    SDL_Renderer *tempr = SDL_CreateRenderer(temp, -1, 0);
    renderer = tempr;
    SDL_SetRenderDrawColor(renderer, InitialColour.r, InitialColour.g, InitialColour.b, 255);
    SDL_RenderClear(renderer);
    log("Cleared");
}
Window::~Window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    printf("window exited\n");
}
SDL_Window *Window::getWindow()
{
    return window;
}
SDL_Renderer *Window::getRenderer()
{
    return renderer;
}
void Window::Activate()
{
    bool finished = 0;
    int i;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    while (!finished)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                finished = 1;
                Window::~Window();
                break;
            }
        }
    }
}

StarterWindow::StarterWindow(char *WindowName)
{
    CreateWindow(WindowName, location(500, 600), size(200, 200), colour(white), SDL_WINDOW_RESIZABLE);
}

CanvasWindow::CanvasWindow(char *WindowName, int ButtonSize)
{
    const size DefaultWindowSize = size(1800, 800);
    CreateWindow(WindowName, location(20, 20), DefaultWindowSize, colour(white), SDL_WINDOW_RESIZABLE);
    log("Window Created");
    fflush(stdout);
    ColourArea = new ResizableArea(location(0), size(DefaultWindowSize.width, 120), colour(60), colour(white), 4, SizeLock::height, window);
    log("Colour area created");
    CanvasArea = new ResizableArea(location(0, 120), size(DefaultWindowSize.width, DefaultWindowSize.height - ((*ColourArea).getSize().height * 2)), colour(128), colour(white), 0, SizeLock::width, window);
    log("Canvas area created");
    size Temp = size(0, 0);
    CanvasItem = new Canvas(CanvasArea);
    CanvasArea->addChild(CanvasItem);
    log("Canvas Created");
    log("items created");
    for (int i = 0; i < 10; i++)
    {
        ColourButtons[i] = *new ColourButton(*(new location((*ColourArea).getPosition().x + 80 + ((int)(i / 2) * ButtonSize), (*ColourArea).getPosition().y + 20 + (ButtonSize * (i % 2)))), size(ButtonSize), colour((defaultColours)i), colour(255), window);
    }
}

void CanvasWindow::Draw()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    (*ColourArea).Draw(renderer, window);
    (*CanvasArea).Draw(renderer, window);
    for (int i = 0; i < sizeof(ColourButtons) / sizeof(ColourButton); i++)
    {
        ColourButtons[i].Draw(renderer);
    }
}

void CanvasWindow::Activate()
{
    int i = 0;
    bool finished = 0;
    bool drawing = 0;
    log("canvas window drawn");
    log("canvas window event loop entered");
    Draw();
    SDL_RenderPresent(renderer);

    while (!finished)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_f:
                    CanvasItem->BrushMode = Fill;
                    break;
                case SDLK_b:
                    CanvasItem->BrushMode = Basic;
                    break;
                }
                break;
            case SDL_WINDOWEVENT_RESIZED:
                SDL_Surface* canvas = SDL_CreateRGBSurface(0, CanvasItem->getSize().width, CanvasItem->getSize().height, 32, 0, 0, 0, 0);
                Uint32 pixels[CanvasItem->getSize().width * CanvasItem->getSize().height];
                SDL_Rect rect;
                rect.x = CanvasItem->getPosition().x;
                rect.y = CanvasItem->getPosition().y;
                rect.w = CanvasItem->getSize().width;
                rect.h = CanvasItem->getSize().height;
                SDL_RenderReadPixels(renderer, &rect, SDL_PIXELFORMAT_ARGB8888, pixels, 0);
                Draw();
                SDL_Surface
                break;
            case SDL_QUIT:
                finished = 1;
                Window::~Window();
                log("window quitted");
                break;
            case SDL_MOUSEBUTTONDOWN:
                drawing = 1;
                if (event.button.y < ColourArea->getPosition().y + ColourArea->getSize().height)
                {
                    for (int i = 0; i < sizeof(ColourButtons) / sizeof(ColourButton); i++)
                    {
                        if (event.button.x >= ColourButtons[i].getPosition().x &&
                            event.button.x <= ColourButtons[i].getPosition().x + ColourButtons[i].getSize().width &&
                            event.button.y >= ColourButtons[i].getPosition().y &&
                            event.button.y <= ColourButtons[i].getPosition().y + ColourButtons[i].getSize().height)
                        {
                            ColourButtons[i].Click((*CanvasItem).getCurrentColour());
                            printf("current colour is %d, %d, %d, %d\n", (*CanvasItem).getCurrentColour()->r, (*CanvasItem).getCurrentColour()->g, (*CanvasItem).getCurrentColour()->b, 255);
                            fflush(stdout);
                        }
                    }
                }
                if (CanvasItem->BrushMode == Fill)
                {
                    CanvasItem->Fill(renderer, window, location(event.button.x, event.button.y));
                    SDL_RenderPresent(renderer);
                }
                break;
            case SDL_MOUSEBUTTONUP:
                drawing = 0;
                break;
            case SDL_MOUSEMOTION:
                if (drawing && CanvasItem->BrushMode == Basic)
                {
                    if (event.button.y >= (*CanvasItem).getPosition().y && event.button.y <= (*CanvasItem).getPosition().y + (*CanvasItem).getSize().height && event.button.x >= (*CanvasItem).getPosition().x && event.button.x <= (*CanvasItem).getPosition().x + (*CanvasItem).getSize().width)
                    {
                        SDL_SetRenderDrawColor(renderer, (*CanvasItem).getCurrentColour()->r, (*CanvasItem).getCurrentColour()->g, (*CanvasItem).getCurrentColour()->b, 255);
                        SDL_RenderDrawLine(renderer, event.button.x - event.motion.xrel, event.button.y - event.motion.yrel, event.button.x, event.button.y);
                        SDL_RenderDrawLine(renderer, event.button.x - event.motion.xrel - 1, event.button.y - event.motion.yrel, event.button.x - 1, event.button.y);
                        SDL_RenderDrawLine(renderer, event.button.x - event.motion.xrel + 1, event.button.y - event.motion.yrel, event.button.x + 1, event.button.y);
                        SDL_RenderDrawLine(renderer, event.button.x - event.motion.xrel, event.button.y - event.motion.yrel - 1, event.button.x, event.button.y - 1);
                        SDL_RenderDrawLine(renderer, event.button.x - event.motion.xrel - 1, event.button.y - event.motion.yrel - 1, event.button.x - 1, event.button.y - 1);
                        SDL_RenderDrawLine(renderer, event.button.x - event.motion.xrel + 1, event.button.y - event.motion.yrel - 1, event.button.x + 1, event.button.y - 1);
                        SDL_RenderDrawLine(renderer, event.button.x - event.motion.xrel, event.button.y - event.motion.yrel + 1, event.button.x, event.button.y + 1);
                        SDL_RenderDrawLine(renderer, event.button.x - event.motion.xrel - 1, event.button.y - event.motion.yrel + 1, event.button.x - 1, event.button.y + 1);
                        SDL_RenderDrawLine(renderer, event.button.x - event.motion.xrel + 1, event.button.y - event.motion.yrel + 1, event.button.x + 1, event.button.y + 1);
                        SDL_RenderPresent(renderer);
                    }
                }
                break;
            }
        }
    }
}