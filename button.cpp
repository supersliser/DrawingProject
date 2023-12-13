#include "area.h"
#include "colour.h"
#include "button.h"
#include "log.h"
void Button::Click()
{
}
void ColourButton::Click(colour *CurrentColour)
{
    *CurrentColour = BackColour;
}

SizeButton::SizeButton()
{
}

SizeButton::SizeButton(location inPosition, size inSize, colour inBC, SDL_Window *window, int SizeItem)
{
    Position = inPosition;
    Size = inSize;
    BackColour = inBC;
    BorderColour = black;
    SizeData = SizeItem;
}

void SizeButton::Click(int *CurrentSize)
{
    *CurrentSize = SizeData;
}

TypeButton::TypeButton()
{
}

TypeButton::TypeButton(location inPosition, size inSize, SDL_Window *window, BrushType inType)
{
    Position = inPosition;
    Size = inSize;
    BackColour = white;
    BorderColour = black;
    Type = inType;
}

void TypeButton::Click(BrushType *inType)
{
    *inType = Type;
}

void TypeButton::Draw(SDL_Renderer *renderer)
{
    if (Type == Fill)
    {
        Button::Draw(renderer);
    }
    else
    {
        Button::Draw(renderer);
        Brush temp;
        temp.CurrentColour = black;
        temp.Draw(renderer, location(Position.x + (Size.width / 2), Position.y + (Size.height / 2)), location(Position.x + (Size.width / 2), Position.y + (Size.height / 2)), 2, 2);
    }
}