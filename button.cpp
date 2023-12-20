#include "area.h"
#include "colour.h"
#include "button.h"
#include "log.h"
void Button::Click()
{
}
void Button::Draw(SDL_Renderer *renderer)
{
    Area::Draw(renderer);
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

void SizeButton::Draw(SDL_Renderer *renderer)
{
    Button::Draw(renderer);
    Brush temp = *new Brush();
    temp.CurrentColour = black;
    temp.Draw(renderer, location(Position.x + (Size.width / 2), Position.y + (Size.height / 2)), location(Position.x + (Size.width / 2), Position.y + (Size.height / 2)), SizeData, SizeData);
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
    switch (Type)
    {
    case Fill:
    {
        Button::Draw(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Rect temp;
        temp.x = Position.x + 5;
        temp.y = Position.y + 5;
        temp.w = Size.width - 10;
        temp.h = Size.height - 10;
        SDL_RenderFillRect(renderer, &temp);
    }
    break;
    case Basic:
    {
        Button::Draw(renderer);
        Brush temp;
        temp.CurrentColour = black;
        temp.Draw(renderer, location(Position.x + (Size.width / 2), Position.y + (Size.height / 2)), location(Position.x + (Size.width / 2), Position.y + (Size.height / 2)), 4, 2);
    }
    break;
    case SquareShape:
    {
        Button::Draw(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_Rect temp;
        temp.x = Position.x + 5;
        temp.y = Position.y + 5;
        temp.w = Size.width - 10;
        temp.h = Size.height - 10;
        SDL_RenderDrawRect(renderer, &temp);
    }
    break;
    case CircleShape:
    {
        Button::Draw(renderer);
        Circle temp = Circle(location(Position.x + (Size.width / 2), Position.y + (Size.height / 2)), 10, black, 1);
        temp.Draw(renderer);
    }
    default:
        Button::Draw(renderer);
        break;
    }
}