#pragma once
#include "location.h"
#include "colour.h"
#include <SDL2/SDL_image.h>
class Area
{
protected:
    location Position;
    size Size;
    colour BackColour;
    colour ForeColour;
    colour BorderColour;
    //    int borderWidth;
    Area **children = nullptr;
    int childCount = 0;
    Area *parent = nullptr;

public:
    Area();
    Area(location inPosition, size inSize, SDL_Window *window);
    Area(location inPosition, size inSize, colour inBC, SDL_Window *window);
    Area(location inPosition, size inSize, colour inBC, colour inBorderC, SDL_Window *window);
    void setPosition(location in);
    void setSize(size in);
    void setBackColour(colour in);
    void setBorderColour(colour in);
    void setParent(Area *inParent);
    void addChild(Area *inArea);
    void killChild(int index);
    Area *getChild(int index);
    location getPosition();
    size getSize();
    colour getBackColour();
    colour getBorderColour();
    void Draw(SDL_Renderer *renderer);
    SDL_Rect *getRect();
};

class ResizableArea : public Area
{
    using Area::Area;

public:
    ResizableArea(location inPosition, size inSize, colour inBC, colour inBorderC, int inBW, SizeLock inLock, SDL_Window *window);
    ResizableArea(location inPosition, size inSize, colour inBC, colour inBorderC, int inBW, SizeLock inLock, Area *Parent, SDL_Window *window);
    void Draw(SDL_Renderer *renderer, SDL_Window *window);
    SDL_Surface *drawing;

protected:
    SizeLock lock = SizeLock::none;
    margin Margin;
};

class Canvas : public Area
{
    using Area::Area;

protected:
    Brush BrushItem;
    void Fillr(SDL_Renderer *renderer, location PointLocation, colour sourceColour);

public:
    colour getPixelColour(SDL_Renderer *renderer, int x, int y);

    void fill(SDL_Renderer *renderer, int wdth, int hght, int x, int y, colour src, colour dst);
    Canvas(Area *inParent);
    colour *getCurrentColour();
    BrushType *getBrushType();
    int *getBrushSize();
    void Fill(SDL_Renderer *renderer, SDL_Window *window, location mouseLocation);
    void BrushDraw(SDL_Renderer *renderer, location lOne, location lTwo);
};