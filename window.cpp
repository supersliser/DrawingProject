#include <window.h>
#include <area.h>

Window::Window()
{
    window = SDL_CreateWindow("Blank Window Name", 50, 50, 400, 500, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, 0);
}
Window::Window(char *WindowName)
{
    window = SDL_CreateWindow(WindowName, 50, 50, 400, 500, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, 0);
}
Window::Window(char *WindowName, location Position, size Size)
{
    window = SDL_CreateWindow(WindowName, Position.x, Position.y, Size.width, Size.height, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, 0);
}
Window::Window(char *WindowName, size Size)
{
    window = SDL_CreateWindow(WindowName, 50, 50, Size.width, Size.height, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, 0);
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
    while (!finished)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                finished = 1;
                break;
            }
        }
    }
}

StarterWindow::StarterWindow(char* WindowName)
{
    window = SDL_CreateWindow(WindowName, 500, 600, 200, 200, SDL_WINDOW_BORDERLESS && SDL_WINDOW_INPUT_GRABBED);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}

CanvasWindow::CanvasWindow(char* WindowName)
{
    window = SDL_CreateWindow(WindowName, 20, 20, 800, 600, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderClear(renderer);
    ColourArea = new ResizableArea(location(0), size(800, 120), colour(60), colour(255), 4, SizeLock::height, window);
    CanvasArea = new ResizableArea(location(0, 160), size(800, 600 - ((*ColourArea).getSize().height * 2)), colour(128), colour(255), 0, SizeLock::width, window);
    CanvasItem = new Canvas(CanvasArea);
    (*CanvasArea).addChild(CanvasItem);
    const int ButtonSize = 25;
    for (int i = 0; i < 8; i++)
    {
        ColourButtons[i] = *new ColourButton(*(new location((*ColourArea).getPosition().x + 80 + ((int)(i / 2) * ButtonSize), (*ColourArea).getPosition().y + 20 + (ButtonSize * (i % 2)))), size(ButtonSize), colour((defaultColours)i), colour(255));
    }
}

void CanvasWindow::Draw()
{
    (*ColourArea).Draw(renderer, window);
    (*CanvasArea).Draw(renderer, window);
    for (int i = 0; i < 8; i++)
    {
        ColourButtons[i].Draw(renderer);
    }
}

void CanvasWindow::Activate()
{
    SDL_Rect brush;
    brush.w = 5;
    brush.h = 5;
    bool finished = 0;
    bool drawing = 0;
    while (!finished)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (drawing)
            {
                if (event.button.y >= (*CanvasItem).getPosition().y && event.button.y <= (*CanvasItem).getPosition().y + (*CanvasItem).getSize().height && event.button.x >= (*CanvasItem).getPosition().x && event.button.x <= (*CanvasItem).getPosition().x + (*CanvasItem).getSize().width)
                {
                    SDL_SetRenderDrawColor(renderer, (*CanvasItem).getCurrentColour().r, (*CanvasItem).getCurrentColour().g, (*CanvasItem).getCurrentColour().b, (*CanvasItem).getCurrentColour().a);
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
                    if (event.button.x >= ColourButtons[i].getPosition().x &&
                        event.button.x <= ColourButtons[i].getPosition().x + ColourButtons[i].getSize().width &&
                        event.button.y >= ColourButtons[i].getPosition().y &&
                        event.button.y <= ColourButtons[i].getPosition().y + ColourButtons[i].getSize().height)
                    {
                        ColourButtons[i].Click(&(*CanvasItem).getCurrentColour());
                        printf("current colour is %d, %d, %d, %d", (*CanvasItem).getCurrentColour().r, (*CanvasItem).getCurrentColour().g, (*CanvasItem).getCurrentColour().b, (*CanvasItem).getCurrentColour().a);
                        fflush(stdout);
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP:
                drawing = 0;
                break;
            }
        }
    }
}

CanvasWindow::~CanvasWindow()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}