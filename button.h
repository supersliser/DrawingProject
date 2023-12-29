#pragma once
#include "area.h"
#include "colour.h"

// A type of area that can be clicked
class Button : public Area
{
    using Area::Area;

public:
    // runs when the button is clicked, function is blank in base class
    void Click();
    void Draw(SDL_Renderer *renderer);
};

// A button that changes the colour of the brush
class ColourButton : public Button
{
    // colour of button = backcolour
    using Button::Button;

public:
    // When the button is clicked, the data at the location of the brush colour is changed to the colour of the button clicked
    void Click(colour *CurrentColour);
};

// A button that changes the size of the brush
class SizeButton : public Button
{
    // the size that the button represents
    int SizeData;

public:
    SizeButton();
    SizeButton(location inPosition, size inSize, colour inBC, SDL_Window *window, int SizeItem);

    void Click(int *CurrentSize);
    void Draw(SDL_Renderer *renderer);
};

// A button that changes the type of brush that is active
class TypeButton : public Button
{
    BrushType Type;

public:
    TypeButton();
    TypeButton(location inPosition, size inSize, SDL_Window *window, BrushType inType);

    void Click(BrushType *inType);
    void Draw(SDL_Renderer *renderer);
};