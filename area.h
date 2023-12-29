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

// A type of Area that can be drawn upon
class Canvas : public Area
{
    using Area::Area;

protected:
    // The brush being used to draw
    Brush BrushItem;
    // The Recursive algorithm used to run the fill command
    void Fillr(SDL_Renderer *renderer, location PointLocation, colour sourceColour);

public:
    // Gets the colour at the specified pixel
    colour getPixelColour(SDL_Renderer *renderer, int x, int y);
    // Canvas Constructor
    Canvas(Area *inParent);
    // Gets a pointer to the current colour of the Brush
    colour *getCurrentColour();
    // Gets a pointer to the current type of Brush set
    BrushType *getBrushType();
    // Gets a pointer to the current size of the Brush
    int *getBrushSize();
    // Initiates the recursive fill
    void Fill(SDL_Renderer *renderer, SDL_Window *window, location mouseLocation);
    // Draws to the canvas with the given brush
    void BrushDraw(SDL_Renderer *renderer, location lOne, location lTwo);
};