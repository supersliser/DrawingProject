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

CanvasWindow::CanvasWindow(char *WindowName, int ButtonSize, size WindowSize, char *outFileLocation)
{
    outputImage = new Image(outFileLocation);
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

CanvasWindow::CanvasWindow(char *WindowName, int ButtonSize, size WindowSize, char *inFileLocation, char *outFileLocation)
{
    inputImage = new Image(inFileLocation);
    ImageExists = true;
    if (WindowSize.width == 0 && WindowSize.height == 0)
    {
        WindowSize = size(inputImage->getImageSize().width + 40, inputImage->getImageSize().height + 280);
    }
    CreateWindow(WindowName, location(20, 20), WindowSize, colour(white), 0);
    outputImage = new Image(outFileLocation);
    fflush(stdout);
    ColourArea = new ResizableArea(location(0), size(WindowSize.width, 120), colour(40), colour(white), 4, SizeLock::height, window);
    CanvasArea = new ResizableArea(location(0, 120), size(WindowSize.width, WindowSize.height - ((*ColourArea).getSize().height * 2)), colour(128), colour(white), 0, SizeLock::none, window);
    size Temp = size(0, 0);
    CanvasItem = new Canvas(CanvasArea);
    CanvasArea->addChild(CanvasItem);
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
}

void CanvasWindow::Draw()
{
    ColourArea->Draw(renderer, window);
    CanvasArea->Draw(renderer, window);
    for (int i = 0; i < sizeof(ColourButtons) / sizeof(ColourButton); i++)
    {
        ColourButtons[i].Draw(renderer);
    }
    for (int i = 0; i < sizeof(SizeButtons) / sizeof(SizeButton); i++)
    {
        SizeButtons[i].Draw(renderer);
    }
    for (int i = 0; i < sizeof(TypeButtons) / sizeof(TypeButton); i++)
    {
        TypeButtons[i].Draw(renderer);
    }
    if (ImageExists)
    {
        inputImage->DrawImage(renderer, *(CanvasItem->getRect()));
    }
    SDL_RenderPresent(renderer);
    log("resised");
}

void CanvasWindow::Activate()
{
    int i = 0;
    bool finished = 0;
    bool drawing = 0;
    bool ctrl = false;
    Square squareBrush;
    Circle circleBrush;
    Image tempImage;

    Draw();

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
            }
            break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_s && ctrl)
                {
                    if (ImageExists)
                    {
                        outputImage->SaveImage(renderer, *(CanvasItem->getRect()));
                    }
                }
                else if (event.key.keysym.sym == SDLK_LCTRL || event.key.keysym.sym == SDLK_RCTRL)
                {
                    ctrl = true;
                }
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_LCTRL || event.key.keysym.sym == SDLK_RCTRL)
                {
                    ctrl = false;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
            {
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
                else if (event.button.x >= CanvasItem->getPosition().x &&
                         event.button.x <= CanvasItem->getPosition().x + CanvasItem->getSize().width &&
                         event.button.y >= CanvasItem->getPosition().y &&
                         event.button.y <= CanvasItem->getPosition().y + CanvasItem->getSize().height)
                {
                    drawing = 1;
                    if (*(CanvasItem->getBrushType()) == Fill)
                    {
                        CanvasItem->Fill(renderer, window, location(event.button.x, event.button.y));
                        SDL_RenderPresent(renderer);
                    }
                    else if (*(CanvasItem->getBrushType()) == SquareShape)
                    {
                        tempImage = *new Image("./tempSurface.png");
                        tempImage.SaveImage(renderer, *CanvasItem->getRect());
                        squareBrush = *new Square(location(event.button.x, event.button.y), size(0, 0), *(CanvasItem->getCurrentColour()), *(CanvasItem->getBrushSize()));
                    }
                    else if (*CanvasItem->getBrushType() == CircleShape)
                    {
                        tempImage = *new Image("./tempSurface.png");
                        tempImage.SaveImage(renderer, *CanvasItem->getRect());
                        circleBrush = *new Circle(location(event.button.x, event.button.y), 0, *(CanvasItem->getCurrentColour()), *(CanvasItem->getBrushSize()));
                    }
                }
            }
            break;

            case SDL_MOUSEBUTTONUP:
            {
                if (*(CanvasItem->getBrushType()) == SquareShape && drawing)
                {
                    tempImage.DrawImage(renderer, *CanvasItem->getRect());
                    squareBrush.Draw(renderer);
                }
                else if (*(CanvasItem->getBrushType()) == CircleShape && drawing)
                {
                    tempImage.DrawImage(renderer, *CanvasItem->getRect());
                    circleBrush.Draw(renderer, *CanvasItem->getRect());
                    location Center = circleBrush.getCenter();
                    int radius = circleBrush.getRadius();
                    CanvasItem->Fill(renderer, window, location(Center.x + radius, Center.y));
                }
                drawing = 0;
            }
            break;

            case SDL_MOUSEMOTION:
            {
                if (drawing && *(CanvasItem->getBrushType()) == Basic)
                {
                    if (event.button.y >= (*CanvasItem).getPosition().y && event.button.y <= (*CanvasItem).getPosition().y + (*CanvasItem).getSize().height && event.button.x >= (*CanvasItem).getPosition().x && event.button.x <= (*CanvasItem).getPosition().x + (*CanvasItem).getSize().width)
                    {
                        CanvasItem->BrushDraw(renderer, location(event.button.x - event.motion.xrel - 1, event.button.y - event.motion.yrel), location(event.button.x - 1, event.button.y));
                    }
                }
                else if (drawing && *(CanvasItem->getBrushType()) == SquareShape)
                {
                    if (event.button.y >= (*CanvasItem).getPosition().y && event.button.y <= (*CanvasItem).getPosition().y + (*CanvasItem).getSize().height && event.button.x >= (*CanvasItem).getPosition().x && event.button.x <= (*CanvasItem).getPosition().x + (*CanvasItem).getSize().width)
                    {
                        tempImage.DrawImage(renderer, *CanvasItem->getRect());
                        squareBrush.DrawTemp(renderer, location(event.button.x, event.button.y));
                    }
                }
                else if (drawing && *(CanvasItem->getBrushType()) == CircleShape)
                {
                    if (event.button.y >= (*CanvasItem).getPosition().y && event.button.y <= (*CanvasItem).getPosition().y + (*CanvasItem).getSize().height && event.button.x >= (*CanvasItem).getPosition().x && event.button.x <= (*CanvasItem).getPosition().x + (*CanvasItem).getSize().width)
                    {
                        tempImage.DrawImage(renderer, *CanvasItem->getRect());
                        circleBrush.DrawTemp(renderer, location(event.button.x, event.button.y), *CanvasItem->getRect());
                    }
                }
                SDL_RenderPresent(renderer);
            }
            break;
            }
        }
    }
}