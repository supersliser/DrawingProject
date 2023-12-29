#pragma once
#include <SDL2/SDL.h>
#include "location.h"
#include "colour.h"
#include "button.h"
#include "image.h"

// stores all data related to a window including its renderer
class Window
{
protected:
    // The window from sdl
    SDL_Window *window;
    // The renderer for the window
    SDL_Renderer *renderer;
    // Creates the window and related renderer
    void CreateWindow(char *Name, location Position, size Size, colour InitialColour, Uint32 Flags);

public:
    // deconstructor
    ~Window();
    // constructor
    Window();
    Window(char *WindowName);
    Window(char *WindowName, location Position, size Size);
    Window(char *WindowName, size Size);
    // getters
    SDL_Window *getWindow();
    SDL_Renderer *getRenderer();
    // Allows a window to begin to detect and trigger events
    void Activate();
};

// The primary window for drawing
class CanvasWindow : public Window
{
protected:
    // The various elements of the window
    ColourButton ColourButtons[10];
    SizeButton SizeButtons[4];
    TypeButton TypeButtons[4];
    Area *ColourArea;
    Area *CanvasArea;
    Canvas *CanvasItem;
    Image *inputImage;
    bool ImageExists;
    Image *outputImage;

public:
    // constructors
    CanvasWindow(char *WindowName, int ButtonSize, size WindowSize, char *outFileLocation);
    CanvasWindow(char *WindowName, int ButtonSize, size WindowSize, char *inFileLocation, char *outFileLocation);
    // intialises the event loop for the window
    void Activate();
    // draws the window and its elements
    void Draw();
};