#pragma once
#include <SDL2/SDL.h>
#include "location.h"
#include "colour.h"
#include "button.h"
#include "image.h"

class Window
{
protected:
    SDL_Window *window;
    SDL_Renderer *renderer;
    void CreateWindow(char *Name, location Position, size Size, colour InitialColour, Uint32 Flags);

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
    StarterWindow(char *WindowName);
};

class CanvasWindow : public Window
{
protected:
    ColourButton ColourButtons[10];
    SizeButton SizeButtons[4];
    TypeButton TypeButtons[2];
    ResizableArea *ColourArea;
    ResizableArea *CanvasArea;
    Canvas *CanvasItem;
    Image inputImage;
    bool ImageExists;

public:
    CanvasWindow(char *WindowName, int ButtonSize, size WindowSize);
    CanvasWindow(char *WindowName, int ButtonSize, size WindowSize, char* inFileLocation);
    void Activate();
    void Draw();
};