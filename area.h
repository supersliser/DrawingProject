#pragma once
#include "location.h"
#include "colour.h"
class Area
{
protected:
    location Position;
    size Size;
    colour BackColour;
    colour ForeColour;
    colour BorderColour;
    //    int borderWidth;
    Area** children = nullptr;
    int childCount = 0;
    Area* parent = nullptr;

public:
    Area();
    Area(location inPosition, size inSize);
    Area(location inPosition, size inSize, colour inBC);
    Area(location inPosition, size inSize, colour inBC, colour inBorderC);
    void setPosition(location in);
    void setSize(size in);
    void setBackColour(colour in);
    void setBorderColour(colour in);
    void setParent(Area* inParent);
    void addChild(Area* inArea);
    void killChild(int index);
    Area* getChild(int index);
    location getPosition();
    size getSize();
    colour getBackColour();
    colour getBorderColour();
    void Draw(SDL_Renderer* renderer);
};

class ResizableArea : public Area
{
	using Area::Area;

public:
	ResizableArea(location inPosition, size inSize, colour inBC, colour inBorderC, int inBW, SizeLock inLock, SDL_Window* window);
    void Draw(SDL_Renderer* renderer, SDL_Window* window);

protected:
	SizeLock lock = SizeLock::none;
	margin Margin;
};