#pragma once
#include <SDL2/SDL.h>
#include "location.h"

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

enum BrushType
{
    Basic = 0,
    Fill,
    SquareShape
};

class colour
{
public:
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 convert(float in);
    float convert(Uint8 in);
    colour();
    colour(defaultColours in);
    colour(Uint8 in);
    colour(Uint8 in, Uint8 inA);
    colour(Uint8 rIn, Uint8 gIn, Uint8 bIn);
};

class Brush
{
public:
    colour CurrentColour;
    BrushType BrushMode;
    int BrushSize;
    void Draw(SDL_Renderer *renderer, location lOne, location lTwo, int num, int maxNum);
};

class Square : Brush, SDL_Rect
{
protected:
    SDL_Rect *getRect();
    void DrawR(SDL_Renderer *renderer, int recurseCount, SDL_Rect rect);
public:
    Square();
    Square(location Position, size inSize, colour inColour, int BrushSize);
    void DrawTemp(SDL_Renderer *renderer, location MousePosition);
    void Draw(SDL_Renderer *renderer);
};