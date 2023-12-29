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