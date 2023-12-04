#include "area.h"
#include "colour.h"
#include "button.h"
void Button::Click()
{
}
void ColourButton::Click(colour *CurrentColour)
{
    *CurrentColour = BackColour;
}