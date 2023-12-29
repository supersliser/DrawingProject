#pragma once
#include <SDL2/SDL.h>
#include "location.h"
#include "log.h"

// A list of default colours
enum defaultColours
{
    black = 0,
    white = 1,
    red = 2,
    yellow = 3,
    green = 4,
    lime = 5,
    darkBlue = 6,
    lightBlue = 7,
    pink = 8,
    purple = 9
};

// The types of brush
enum BrushType
{
    Basic = 0,
    Fill,
    SquareShape,
    CircleShape
};

// Stores an RGB colour
class colour
{
public:
    Uint8 r;
    Uint8 g;
    Uint8 b;
    // converts a number from 0 - 1 to 0 to 255
    Uint8 convert(float in);
    // converts a number from 0 - 255 to 0 to 1
    float convert(Uint8 in);

    // constructors
    colour();
    colour(defaultColours in);
    colour(Uint8 in);
    colour(Uint8 rIn, Uint8 gIn, Uint8 bIn);
};

// Stores all data about a brush
class Brush
{
public:
    // the colour of the brush
    colour CurrentColour;
    // the type of brush
    BrushType BrushMode;
    // the size of the brush
    int BrushSize;
    // Draws a line between 2 points, this avoids break up between pixels when pen is moved too fast
    void Draw(SDL_Renderer *renderer, location lOne, location lTwo, int num, int maxNum);
};

// A type of brush that draws a rectangle
class Rectangle : Brush, SDL_Rect
{
protected:
    SDL_Rect *getRect();
    // Draws the rectangle recursively for the size of the brush
    void DrawR(SDL_Renderer *renderer, int recurseCount, SDL_Rect rect);

public:
    // constructors
    Rectangle();
    Rectangle(location Position, size inSize, colour inColour, int BrushSize);
    // Draws the temporary rubber band version
    void DrawTemp(SDL_Renderer *renderer, location MousePosition);
    // Draws the true version
    void Draw(SDL_Renderer *renderer);
};

// A type of brush that draws a circle
class Circle : Brush
{
protected:
    // The location of the center of the circle
    location Center;
    // The radius of the circle
    int radius;

    // The actual drawing function
    void DrawCircle(SDL_Renderer *renderer, SDL_Rect CanvasSize, int BrushSize);

public:
    // constructors
    Circle();
    Circle(location inCenter, int inRadius, colour inColour, int BrushSize);
    // Recursively draws individual pixels
    void DrawPoint(SDL_Renderer *renderer, location PointLocation, int r);
    // draws a temporary rubber banding version
    void DrawTemp(SDL_Renderer *renderer, location MouseDistance, SDL_Rect CanvasSize);
    // draws a true version
    void Draw(SDL_Renderer *renderer, SDL_Rect CanvasSize);
    location getCenter();
    int getRadius();
};