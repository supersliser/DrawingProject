#pragma once
#include <SDL2/SDL.h>
#include "location.h"
#include "colour.h"
#include "button.h"

class Window
{
protected:
    SDL_Window *window;
    SDL_Renderer *renderer;
    void CreateWindow(char* Name, location Position, size Size, colour InitialColour, Uint32 Flags);
public:
    Window();
    ~Window();
    Window(char *WindowName);
    Window(char *WindowName, location Position, size Size);
    Window(char *WindowName, size Size);
    SDL_Window *getWindow();
    SDL_Renderer *getRenderer();
    void Activate();
};

class StarterWindow : public Window
{
public:
    StarterWindow(char* WindowName);
};

class CanvasWindow : public Window
{
protected:
    ColourButton ColourButtons[8];
    ResizableArea* ColourArea;
    ResizableArea* CanvasArea;
    Canvas* CanvasItem;
public:
    CanvasWindow(char *WindowName, int ButtonSize);
    void Activate();
    void Draw();
};