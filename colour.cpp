#include "colour.h"

Uint8 colour::convert(float in)
{
    return in * 255;
}
float colour::convert(Uint8 in)
{
    return in / 255;
}
colour::colour()
{
    r = 0;
    g = 0;
    b = 0;
}
colour::colour(defaultColours in)
{
    switch (in)
    {
    case 0:
        r = 1;
        g = 1;
        b = 1;
        break;
    case 1:
        r = 255;
        g = 255;
        b = 255;
        break;
    case 2:
        r = 255;
        g = 0;
        b = 0;
        break;
    case 3:
        r = 255;
        g = 255;
        b = 0;
        break;
    case 4:
        r = 0;
        g = 128;
        b = 0;
        break;
    case 5:
        r = 0;
        g = 255;
        b = 0;
        break;
    case 6:
        r = 0;
        g = 208;
        b = 255;
        break;
    case 7:
        r = 0;
        g = 0;
        b = 255;
        break;
    case 8:
        r = 255;
        g = 105;
        b = 217;
        break;
    case 9:
        r = 155;
        g = 47;
        b = 237;
        break;
    default:
        r = 1;
        g = 1;
        b = 1;
        break;
    }
}
colour::colour(Uint8 in)
{
    r = in;
    g = in;
    b = in;
}
colour::colour(Uint8 in, Uint8 inA)
{
    r = in;
    g = in;
    b = in;
}
colour::colour(Uint8 rIn, Uint8 gIn, Uint8 bIn)
{
    r = rIn;
    g = gIn;
    b = bIn;
}

void Brush::Draw(SDL_Renderer *renderer, location lOne, location lTwo, int num, int maxNum)
{
    if (num > 0)
    {
        SDL_SetRenderDrawColor(renderer, CurrentColour.r, CurrentColour.g, CurrentColour.b, (Uint8)(int)(255 * (num / maxNum)));
        SDL_RenderDrawLine(renderer, lOne.x, lOne.y, lTwo.x, lTwo.y);
        Draw(renderer, location(lOne.x - 1, lOne.y), location(lTwo.x - 1, lTwo.y), num - 1, maxNum);
        Draw(renderer, location(lOne.x + 1, lOne.y), location(lTwo.x + 1, lTwo.y), num - 1, maxNum);
        Draw(renderer, location(lOne.x, lOne.y - 1), location(lTwo.x, lTwo.y - 1), num - 1, maxNum);
        Draw(renderer, location(lOne.x, lOne.y + 1), location(lTwo.x, lTwo.y + 1), num - 1, maxNum);
    }
    else
    {
        return;
    }
}
SDL_Rect *Square::getRect()
{
    SDL_Rect temp;
    temp.x = x;
    temp.y = y;
    temp.w = w;
    temp.h = h;
    return &temp;
}

Square::Square()
{
}

Square::Square(location Position, size inSize, colour inColour, int BrushSize)
{
    x = Position.x;
    y = Position.y;
    w = inSize.width;
    h = inSize.height;

    CurrentColour = inColour;
    Square::BrushSize = BrushSize;
}

void Square::DrawTemp(SDL_Renderer *renderer, location MousePosition)
{
    w = MousePosition.x - x;
    h = MousePosition.y - y;
    SDL_SetRenderDrawColor(renderer, CurrentColour.r, CurrentColour.g, CurrentColour.b, 128);
    SDL_RenderDrawRect(renderer, getRect());
    SDL_RenderPresent(renderer);
}

void Square::Draw(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, CurrentColour.r, CurrentColour.g, CurrentColour.b, 255);
    DrawR(renderer, BrushSize, *getRect());
    SDL_RenderPresent(renderer);
}

void Square::DrawR(SDL_Renderer *renderer, int recurseCount, SDL_Rect rect)
{
    SDL_RenderDrawRect(renderer, &rect);

    if (recurseCount == 0)
    {
        return;
    }
    SDL_Rect temp = rect;
    temp.x -= 1;
    DrawR(renderer, recurseCount - 1, temp);
    temp.x += 2;
    DrawR(renderer, recurseCount - 1, temp);
    temp.x -=1;
    temp.y -=1;
    DrawR(renderer, recurseCount - 1, temp);
    temp.y +=2;
    DrawR(renderer, recurseCount - 1, temp);
}