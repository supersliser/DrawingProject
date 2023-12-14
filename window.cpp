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

CanvasWindow::CanvasWindow(char *WindowName, int ButtonSize, size WindowSize)
{
    CreateWindow(WindowName, location(20, 20), WindowSize, colour(white), 0);
    log("Window Created");
    fflush(stdout);
    ColourArea = new ResizableArea(location(0), size(WindowSize.width, 120), colour(40), colour(white), 4, SizeLock::height, window);
    log("Colour area created");
    CanvasArea = new ResizableArea(location(0, 120), size(WindowSize.width, WindowSize.height - ((*ColourArea).getSize().height * 2)), colour(128), colour(white), 0, SizeLock::none, window);
    log("Canvas area created");
    size Temp = size(0, 0);
    CanvasItem = new Canvas(CanvasArea);
    CanvasArea->addChild(CanvasItem);
    log("Canvas Created");
    log("items created");
    for (int i = 0; i < sizeof(ColourButtons) / sizeof(ColourButton); i++)
    {
        ColourButtons[i] = *new ColourButton(location(80 + ((int)(i / 2) * ButtonSize), 20 + (ButtonSize * (i % 2))), size(ButtonSize), colour((defaultColours)i), colour(255), window);
        ColourArea->addChild(&(ColourButtons[i]));
    }
    for (int i = 0; i < sizeof(SizeButtons) / sizeof(SizeButton); i++)
    {
        SizeButtons[i] = *new SizeButton(location(20 + ColourButtons[9].getPosition().x + ColourButtons[9].getSize().width + (i * ButtonSize), 20), size(ButtonSize), colour(255 - (i * 64)), window, i + 1);
        ColourArea->addChild(&(SizeButtons[i]));
    }
    for (int i = 0; i < sizeof(TypeButtons) / sizeof(TypeButton); i++)
    {
        TypeButtons[i] = *new TypeButton(location(20 + ColourButtons[9].getPosition().x + ColourButtons[9].getSize().width + (i * ButtonSize), 60), size(ButtonSize), window, (BrushType)i);
        ColourArea->addChild(&(TypeButtons[i]));
    }
    ImageExists = false;
}

CanvasWindow::CanvasWindow(char *WindowName, int ButtonSize, size WindowSize, char *inFileLocation)
{
    CreateWindow(WindowName, location(20, 20), WindowSize, colour(white), 0);
    log("Window Created");
    fflush(stdout);
    ColourArea = new ResizableArea(location(0), size(WindowSize.width, 120), colour(40), colour(white), 4, SizeLock::height, window);
    CanvasArea = new ResizableArea(location(0, 120), size(WindowSize.width, WindowSize.height - ((*ColourArea).getSize().height * 2)), colour(128), colour(white), 0, SizeLock::none, window);
    size Temp = size(0, 0);
    CanvasItem = new Canvas(CanvasArea);
    CanvasArea->addChild(CanvasItem);
    log("Canvas Created");
    for (int i = 0; i < sizeof(ColourButtons) / sizeof(ColourButton); i++)
    {
        ColourButtons[i] = *new ColourButton(location(80 + ((int)(i / 2) * ButtonSize), 20 + (ButtonSize * (i % 2))), size(ButtonSize), colour((defaultColours)i), colour(255), window);
        ColourArea->addChild(&(ColourButtons[i]));
    }
    for (int i = 0; i < sizeof(SizeButtons) / sizeof(SizeButton); i++)
    {
        SizeButtons[i] = *new SizeButton(location(20 + ColourButtons[9].getPosition().x + ColourButtons[9].getSize().width + (i * ButtonSize), 20), size(ButtonSize), colour(255 - (i * 64)), window, i + 1);
        ColourArea->addChild(&(SizeButtons[i]));
    }
    for (int i = 0; i < sizeof(TypeButtons) / sizeof(TypeButton); i++)
    {
        TypeButtons[i] = *new TypeButton(location(20 + ColourButtons[9].getPosition().x + ColourButtons[9].getSize().width + (i * ButtonSize), 60), size(ButtonSize), window, (BrushType)i);
        ColourArea->addChild(&(TypeButtons[i]));
    }
    inputImage = *new Image(inFileLocation);
    ImageExists = true;
}

void CanvasWindow::Draw()
{
    (*ColourArea).Draw(renderer, window);
    (*CanvasArea).Draw(renderer, window);
    SDL_RenderPresent(renderer);
}

void CanvasWindow::Activate()
{
    int i = 0;
    bool finished = 0;
    bool drawing = 0;
    log("canvas window drawn");
    log("canvas window event loop entered");
    Draw();
    // SDL_RenderSetClipRect(renderer, CanvasItem->getRect());
    if (ImageExists)
    {
        inputImage.DrawImage(renderer, CanvasItem->getRect());
        SDL_RenderPresent(renderer);
        log("image drawn");
    }
    while (!finished)
    {

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
            {
                finished = 1;
                Window::~Window();
                log("window quitted");
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
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
                    for (int i = 0; i < sizeof(SizeButtons) / sizeof(SizeButton); i++)
                    {
                        if (event.button.x >= SizeButtons[i].getPosition().x &&
                            event.button.x <= SizeButtons[i].getPosition().x + SizeButtons[i].getSize().width &&
                            event.button.y >= SizeButtons[i].getPosition().y &&
                            event.button.y <= SizeButtons[i].getPosition().y + SizeButtons[i].getSize().height)
                        {
                            SizeButtons[i].Click(CanvasItem->getBrushSize());
                            printf("current brush size is %d\n", *(CanvasItem->getBrushSize()));
                            fflush(stdout);
                        }
                    }
                    for (int i = 0; i < sizeof(TypeButtons) / sizeof(TypeButton); i++)
                    {
                        if (event.button.x >= TypeButtons[i].getPosition().x &&
                            event.button.x <= TypeButtons[i].getPosition().x + TypeButtons[i].getSize().width &&
                            event.button.y >= TypeButtons[i].getPosition().y &&
                            event.button.y <= TypeButtons[i].getPosition().y + TypeButtons[i].getSize().height)
                        {
                            TypeButtons[i].Click(CanvasItem->getBrushType());
                            printf("current brush type is %d\n", (int)*(CanvasItem->getBrushType()));
                            fflush(stdout);
                        }
                    }
                }
                if (*(CanvasItem->getBrushType()) == Fill &&
                    (event.button.x >= CanvasItem->getPosition().x &&
                     event.button.x <= CanvasItem->getPosition().x + CanvasItem->getSize().width &&
                     event.button.y >= CanvasItem->getPosition().y &&
                     event.button.y <= CanvasItem->getPosition().y + CanvasItem->getSize().height))
                {
                    CanvasItem->Fill(renderer, window, location(event.button.x, event.button.y));
                    SDL_RenderPresent(renderer);
                }
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                drawing = 0;
                break;
            }
            case SDL_MOUSEMOTION:
            {
                if (drawing && *(CanvasItem->getBrushType()) == Basic)
                {
                    if (event.button.y >= (*CanvasItem).getPosition().y && event.button.y <= (*CanvasItem).getPosition().y + (*CanvasItem).getSize().height && event.button.x >= (*CanvasItem).getPosition().x && event.button.x <= (*CanvasItem).getPosition().x + (*CanvasItem).getSize().width)
                    {
                        CanvasItem->BrushDraw(renderer, location(event.button.x - event.motion.xrel - 1, event.button.y - event.motion.yrel), location(event.button.x - 1, event.button.y));
                        SDL_RenderPresent(renderer);
                    }
                }
                break;
            }
            }
        }
    }
}