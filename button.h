#pragma once
#include "area.h"
#include "colour.h"

class Button : public Area
{
    using Area::Area;

public:
    void Click();
    void Draw(SDL_Renderer *renderer);
};

class ColourButton : public Button
{
    using Button::Button;

public:
    void Click(colour *CurrentColour);
};

class SizeButton : public Button
{
    int SizeData;

public:
    SizeButton();
    SizeButton(location inPosition, size inSize, colour inBC, SDL_Window *window, int SizeItem);

    void Click(int *CurrentSize);
    void Draw(SDL_Renderer *renderer);
};

class TypeButton : public Button
{
    BrushType Type;

public:
    TypeButton();
    TypeButton(location inPosition, size inSize, SDL_Window *window, BrushType inType);

    void Click(BrushType *inType);
    void Draw(SDL_Renderer *renderer);
};