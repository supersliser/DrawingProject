#include <SDL2/SDL.h>
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
    a = 255;
}
colour::colour(defaultColours in)
{
    a = 255;
    switch (in)
    {
    case 0:
        r = 0;
        g = 0;
        b = 0;
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
        g = 50;
        b = 0;
        break;
    case 5:
        r = 0;
        g = 255;
        b = 0;
        break;
    case 6:
        r = 0;
        g = 0;
        b = 50;
        break;
    case 7:
        r = 0;
        g = 0;
        b = 255;
        break;
    default:
        r = 0;
        g = 0;
        b = 0;
        break;
    }
}
colour::colour(Uint8 in)
{
    r = in;
    g = in;
    b = in;
    a = 255;
}
colour::colour(Uint8 in, Uint8 inA)
{
    r = in;
    g = in;
    b = in;
    a = inA;
}
colour::colour(Uint8 rIn, Uint8 gIn, Uint8 bIn)
{
    r = rIn;
    g = gIn;
    b = bIn;
    a = 255;
}
colour::colour(Uint8 rIn, Uint8 gIn, Uint8 bIn, Uint8 aIn)
{
    r = rIn;
    g = gIn;
    b = bIn;
    a = aIn;
}