#pragma once
#include "area.h"
#include "colour.h"

class Button : public Area
{
    using Area::Area;
public:
    void Click();
};

class ColourButton : public Button
{
    using Button::Button;
public:
    void Click(colour* CurrentColour);
};