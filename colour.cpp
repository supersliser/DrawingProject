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
    temp.x -= 1;
    temp.y -= 1;
    DrawR(renderer, recurseCount - 1, temp);
    temp.y += 2;
    DrawR(renderer, recurseCount - 1, temp);
}

Circle::Circle()
{
}
Circle::Circle(location inCenter, int inRadius, colour inColour, int BrushSize)
{
    Center = inCenter;
    radius = inRadius;
    CurrentColour = inColour;
    Brush::BrushSize = BrushSize;
}

void Circle::DrawCircle(SDL_Renderer *renderer)
{
    int x = radius;
    int y = 0;
    int error = 1 - radius;

    while (x >= y)
    {
        /* 1 draw call for each octant - ensure coordinates are valid before drawing */
        if ((x + Center.x) >= 0 && (x + Center.x) < width && (y + Center.y) >= 0 && (y + Center.y) < height)
            SDL_RenderDrawPoint(renderer, x + Center.x, y + Center.y);
        /* draw point in octant 1 if coordinate is valid */
        if ((y + Center.x) >= 0 && (y + Center.x) < width && (x + Center.y) >= 0 && (x + Center.y) < height)
            SDL_RenderDrawPoint(renderer, y + Center.x, x + Center.y);
        /* draw point in octant 2 if coordinate is valid */
        if ((-x + Center.x) >= 0 && (-x + Center.x) < width && (y + Center.y) >= 0 && (y + Center.y) < height)
            SDL_RenderDrawPoint(renderer, -x + Center.x, y + Center.y);
        /* draw point in octant 3 if coordinate is valid */
        if ((-y + Center.x) >= 0 && (-y + Center.x) < width && (x + Center.y) >= 0 && (x + Center.y) < height)
            SDL_RenderDrawPoint(renderer, -y + Center.x, x + Center.y);
        /* draw point in octant 4 if coordinate is valid */
        if ((-x + Center.x) >= 0 && (-x + Center.x) < width && (-y + Center.y) >= 0 && (-y + Center.y) < height)
            SDL_RenderDrawPoint(renderer, -x + Center.x, -y + Center.y);
        /* draw point in octant 5 if coordinate is valid */
        if ((-y + Center.x) >= 0 && (-y + Center.x) < width && (-x + Center.y) >= 0 && (-x + Center.y) < height)
            SDL_RenderDrawPoint(renderer, -y + Center.x, -x + Center.y);
        /* draw point in octant 6 if coordinate is valid */
        if ((x + Center.x) >= 0 && (x + Center.x) < width && (-y + Center.y) >= 0 && (-y + Center.y) < height)
            SDL_RenderDrawPoint(renderer, x + Center.x, -y + Center.y);
        /* draw point in octant 7 if coordinate is valid */
        if ((y + Center.x) >= 0 && (y + Center.x) < width && (-x + Center.y) >= 0 && (-x + Center.y) < height)
            SDL_RenderDrawPoint(renderer, y + Center.x, -x + Center.y);
        /* draw point in octant 8 if coordinate is valid */
        y++; /* increment y coordinate */
        if (error < 0)
        {
            error += 2 * y + 1;
        }
        else
        {
            x--;
            error += 2 * (y - x) + 1;
        }
    }
}

void Circle::DrawTemp(SDL_Renderer *renderer, location MousePosition)
{
    if (MousePosition.x < Center.x)
    {
        radius = Center.x - MousePosition.x;
    }
    else
    {
        radius = MousePosition.x - Center.x;
    }
    if (MousePosition.y < Center.y)
    {
        radius += Center.y - MousePosition.y;
    }
    else
    {
        radius = MousePosition.y - Center.y;
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    DrawCircle(renderer);
}

void Circle::Draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, CurrentColour.r, CurrentColour.g, CurrentColour.b, 255);
    radius += BrushSize / 2;
    DrawCircle(renderer);
    radius -= BrushSize;
    DrawCircle(renderer);
}