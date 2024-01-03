#include "area.h"
#include "log.h"
Area::Area()
{
	Position = location(0);
	Size = size(50);
	BackColour = colour(white);
	BorderColour = colour(255);
}
Area::Area(location inPosition, size inSize, SDL_Window *window)
{
	Position = inPosition;
	Size = inSize;
	BackColour = colour(white);
	BorderColour = colour(255);
}
Area::Area(location inPosition, size inSize, colour inBC, SDL_Window *window)
{
	Position = inPosition;
	Size = inSize;
	BackColour = inBC;
	BorderColour = colour(255);
}
Area::Area(location inPosition, size inSize, colour inBC, colour inBorderC, SDL_Window *window)
{
	Position = inPosition;
	Size = inSize;
	BackColour = inBC;
	BorderColour = inBorderC;
}
void Area::setPosition(location in)
{
	Position = in;
}
void Area::setSize(size in)
{
	Size = in;
}
void Area::setBackColour(colour in)
{
	BackColour = in;
}
void Area::setBorderColour(colour in)
{
	BorderColour = in;
}
void Area::setParent(Area *inParent)
{
	parent = inParent;
}
void Area::addChild(Area *inArea)
{
	// if there are no children, the area must first be defined, then it can be redefined after
	if (childCount == 0)
	{
		children = (Area **)malloc(sizeof(Area *));
	}
	else
	{
		children = (Area **)realloc(children, sizeof(Area *) * childCount + 1);
	}
	childCount++;
	// assigns the actual pointer
	children[childCount - 1] = inArea;
	(*inArea).setParent(this);
}
void Area::killChild(int index)
{
	// Releases the memory to the heap
	free(children[index]);
	// Moves all other children after this child down by 1
	for (int i = index; i < childCount - 1; i++)
	{
		children[i] = children[i + 1];
	}
	childCount--;
	children = (Area **)realloc(children, sizeof(Area *) * childCount);
}
Area *Area::getChild(int index)
{
	return children[index];
}
location Area::getPosition()
{
	location temp;
	// if it has a parent then the position should be absolute as a pose to relative to the parent
	if (parent == nullptr)
	{
		temp.x = Position.x;
		temp.y = Position.y;
	}
	else
	{
		temp.x = Position.x + (*parent).getPosition().x;
		;
		temp.y = Position.y + (*parent).getPosition().y;
		;
	}
	return temp;
}
size Area::getSize()
{
	return Size;
}
colour Area::getBackColour()
{
	return BackColour;
}
colour Area::getBorderColour()
{
	return BorderColour;
}
void Area::Draw(SDL_Renderer *renderer)
{
	SDL_Rect temp = *getRect();
	SDL_SetRenderDrawColor(renderer, BackColour.r, BackColour.g, BackColour.b, 255);
	// Draws the background
	SDL_RenderFillRect(renderer, &temp);
	SDL_SetRenderDrawColor(renderer, BorderColour.r, BorderColour.g, BorderColour.b, 255);
	// Draws the border colour
	SDL_RenderDrawRect(renderer, &temp);
	// Draws all children if any
	for (int i = 0; i < childCount; i++)
	{
		(*children[i]).Draw(renderer);
	}
}

SDL_Rect *Area::getRect()
{
	SDL_Rect output;
	output.x = getPosition().x;
	output.y = getPosition().y;
	output.w = getSize().width;
	output.h = getSize().height;
	return &output;
}

Canvas::Canvas(Area *inParent)
{
	Position = location(20, 20);
	Size = size((*inParent).getSize().width - 40, (*inParent).getSize().height - 40);
	BackColour = colour(white);
	BorderColour = colour(white);
	BrushItem.CurrentColour = black;
	BrushItem.BrushMode = Basic;
	BrushItem.BrushSize = 2;
}

colour *Canvas::getCurrentColour()
{
	return &BrushItem.CurrentColour;
}

// source based on "Eike Anderson" ref:1
colour Canvas::getPixelColour(SDL_Renderer *renderer, int x, int y)
{
	colour pcol;
	Uint32 pixels[10]; /* pixel and safety buffer (although 1 should be enough) */
	pcol.r = 255;
	pcol.g = 255;
	pcol.b = 255;
	if (x >= 0 && x < Size.width + getPosition().x && y >= 0 && y < Size.height + getPosition().y) /* test if the coordinates are valid */
	{
		SDL_Rect rect; /* SDL rectangle of 1 pixel */
		/* 2 helper structures to get SDL to generate the right pixel format */
		SDL_Surface *s = SDL_CreateRGBSurface(0, 5, 5, 32, 0, 0, 0, 0);				/* helper 1 */
		SDL_Surface *ns = SDL_ConvertSurfaceFormat(s, SDL_PIXELFORMAT_ARGB8888, 0); /* 2 */
		rect.x = x;
		rect.y = y;
		rect.w = 1;
		rect.h = 1;
		/* renderer, pixel, target format, target array, safety value 5 (1 was needed) */
		if (!SDL_RenderReadPixels(renderer, &rect, SDL_PIXELFORMAT_ARGB8888, pixels, 5))
		{ /* pixel, pixel format (from helper 2), colour channels by reference */
			SDL_GetRGB(pixels[0], ns->format, &(pcol.r), &(pcol.g), &(pcol.b));
		}
		SDL_FreeSurface(s);	 /* free helper 1 */
		SDL_FreeSurface(ns); /* free helper 2 */
	}
	return pcol;
}

void Canvas::Fill(SDL_Renderer *renderer, SDL_Window *window, location mouseLocation)
{
	SDL_SetRenderDrawColor(renderer, BrushItem.CurrentColour.r, BrushItem.CurrentColour.g, BrushItem.CurrentColour.b, 255);
	Fillr(renderer, mouseLocation, getPixelColour(renderer, mouseLocation.x, mouseLocation.y));
}

void Canvas::Fillr(SDL_Renderer *renderer, location PointLocation, colour sourceColour)
{
	colour pcol = getPixelColour(renderer, PointLocation.x, PointLocation.y);
	if (PointLocation.x < getPosition().x || PointLocation.y < getPosition().y || PointLocation.x > Size.width + getPosition().x || PointLocation.y > Size.height + getPosition().y)
	{
		return;
	}
	if (pcol.r != sourceColour.r || pcol.g != sourceColour.g || pcol.b != sourceColour.b)
	{
		return;
	}
	if (sourceColour.r == BrushItem.CurrentColour.r && sourceColour.g == BrushItem.CurrentColour.g && sourceColour.b == BrushItem.CurrentColour.b)
	{
		return;
	}
	SDL_RenderDrawPoint(renderer, PointLocation.x, PointLocation.y);
	Fillr(renderer, location(PointLocation.x - 1, PointLocation.y), sourceColour);
	Fillr(renderer, location(PointLocation.x, PointLocation.y - 1), sourceColour);
	Fillr(renderer, location(PointLocation.x + 1, PointLocation.y), sourceColour);
	Fillr(renderer, location(PointLocation.x, PointLocation.y + 1), sourceColour);
}
// source based on "Eike Anderson" ends here

void Canvas::BrushDraw(SDL_Renderer *renderer, location lOne, location lTwo)
{
	BrushItem.Draw(renderer, lOne, lTwo, BrushItem.BrushSize, BrushItem.BrushSize);
}

BrushType *Canvas::getBrushType()
{
	return &(BrushItem.BrushMode);
}

int *Canvas::getBrushSize()
{
	return &(BrushItem.BrushSize);
}