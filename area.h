#pragma once
#include "location.h"
#include "colour.h"
#include <SDL2/SDL_image.h>

// A resizable square shaped area
class Area
{
protected:
    // The location of the top left corner relative to the position of the parent area
    location Position;
    // The size of the area
    size Size;
    // The background colour of the area
    colour BackColour;
    // The colour of the border of the area
    colour BorderColour;
    // An array of children areas
    Area **children = nullptr;
    // The number of children
    int childCount = 0;
    // The parent area of this area.
    Area *parent = nullptr;

public:
    // Constructors
    Area();
    Area(location inPosition, size inSize, SDL_Window *window);
    Area(location inPosition, size inSize, colour inBC, SDL_Window *window);
    Area(location inPosition, size inSize, colour inBC, colour inBorderC, SDL_Window *window);
    // Setters
    void setPosition(location in);
    void setSize(size in);
    void setBackColour(colour in);
    void setBorderColour(colour in);
    void setParent(Area *inParent);
    // Adds a pointer to a child area
    void addChild(Area *inArea);
    // Removes a pointer to a child area
    void killChild(int index);
    // Gets the child at a given index
    Area *getChild(int index);
    // Getters
    location getPosition();
    size getSize();
    colour getBackColour();
    colour getBorderColour();
    SDL_Rect *getRect();
    // Draws the area by drawing the background area, then drawing all child components
    void Draw(SDL_Renderer *renderer);
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