#include <SDL2/SDL.h>
#include "location.h"
#include "colour.h"
#include "button.h"

class Window
{
protected:
    SDL_Window *window;
    SDL_Renderer *renderer;

public:
    Window();
    Window(char *WindowName);
    Window(char *WindowName, location Position, size Size);
    Window(char *WindowName, size Size);
    SDL_Window *getWindow();
    SDL_Renderer *getRenderer();
    void Activate();
};

class StarterWindow : public Window
{
    using Window::Window;

public:
    StarterWindow(char* WindowName);
};

class CanvasWindow : public Window
{
    using Window::Window;

protected:
    ColourButton ColourButtons[8];
    ResizableArea* ColourArea;
    ResizableArea* CanvasArea;
    Canvas* CanvasItem;
public:
    CanvasWindow(char* WindowName);
    void Activate();
    void Draw();
};