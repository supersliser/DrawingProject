#include "location.h"

location::location()
{
	x = 0;
	y = 0;
}
location::location(int in)
{
	x = in;
	y = in;
}
location::location(int inX, int inY)
{
	x = inX;
	y = inY;
}
location location::Add(location in)
{
	return location(x + in.x, y + in.y);
}

size::size()
{
	width = 0;
	height = 0;
}
size::size(int in)
{
	width = in;
	height = in;
}
size::size(int inWidth, int inHeight)
{
	width = inWidth;
	height = inHeight;
}

margin::margin()
{
	top = 0;
	bottom = 0;
	left = 0;
	right = 0;
}
margin::margin(int inT, int inB, int inL, int inR)
{
	top = inT;
	bottom = inB;
	left = inL;
	right = inR;
}
margin::margin(location inLoc)
{
	top = inLoc.y;
	left = inLoc.x;
	bottom = inLoc.y;
	right = inLoc.x;
}