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
//    void setBorderWidth(int in)
//    {
//        borderWidth = in;
//    }
void Area::setParent(Area *inParent)
{
	parent = inParent;
}
void Area::addChild(Area *inArea)
{
	if (childCount == 0)
	{
		children = (Area **)malloc(sizeof(Area *));
	}
	childCount++;
	children = (Area **)realloc(children, sizeof(Area *) * childCount);
	children[childCount - 1] = inArea;
	(*inArea).setParent(this);
}
void Area::killChild(int index)
{
	free(children[index]);
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
//    int getBorderWidth()
//    {
//        return borderWidth;
//    }
void Area::Draw(SDL_Renderer *renderer)
{
	SDL_Rect temp;
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
	temp.w = Size.width;
	temp.h = Size.height;
	SDL_SetRenderDrawColor(renderer, BackColour.r, BackColour.g, BackColour.b, BackColour.a);
	SDL_RenderFillRect(renderer, &temp);
	SDL_SetRenderDrawColor(renderer, BorderColour.r, BorderColour.g, BorderColour.b, BorderColour.a);
	for (int i = 0; i < childCount; i++)
	{
		(*children[i]).Draw(renderer);
	}
}

ResizableArea::ResizableArea(location inPosition, size inSize, colour inBC, colour inBorderC, int inBW, SizeLock inLock, SDL_Window *window)
{
	if (parent == nullptr)
	{
		Position = inPosition;
	}
	else
	{
		Position.x = (*parent).getSize().width - Position.x;
		Position.y = (*parent).getSize().height - Position.y;
	}
	Size = inSize;
	BackColour = inBC;
	BorderColour = inBorderC;
	lock = inLock;
	log("properties assigned");
	size Temp = size(0, 0);
	SDL_GetWindowSize(window, &Temp.width, &Temp.height);
	printf("window size is x= %d, y= %d\n", Temp.width, Temp.height);
	fflush(stdout);
	Margin.top = Position.y;
	Margin.left = Position.x;
	Margin.bottom = Temp.height - (Margin.top + Size.height);
	Margin.right = Temp.width - (Margin.left + Size.width);
	log("margin assigned");
}
ResizableArea::ResizableArea(location inPosition, size inSize, colour inBC, colour inBorderC, int inBW, SizeLock inLock, Area *Parent, SDL_Window *window)
{
	parent = Parent;
	if (parent == nullptr)
	{
		Position = inPosition;
	}
	else
	{
		Position.x = (*parent).getSize().width - Position.x;
		Position.y = (*parent).getSize().height - Position.y;
	}
	Size = inSize;
	BackColour = inBC;
	BorderColour = inBorderC;
	lock = inLock;

	log("properties assigned");
	size Temp = size(0, 0);
	SDL_GetWindowSize(window, &Temp.width, &Temp.height);
	printf("window size is x= %d, y= %d\n", Temp.width, Temp.height);
	fflush(stdout);
	Margin.top = Position.y;
	Margin.left = Position.x;
	Margin.bottom = Temp.height - (Margin.top + Size.height);
	Margin.right = Temp.width - (Margin.left + Size.width);
}
void ResizableArea::Draw(SDL_Renderer *renderer, SDL_Window *window)
{
	size temp;
	if (parent == nullptr)
	{
		SDL_GetWindowSize(window, &(temp.width), &(temp.height));
	}
	else
	{
		temp = (*parent).getSize();
	}
	switch (lock)
	{
	case SizeLock::none:
		Size.width = temp.width - Margin.right;
		Size.height = temp.height - Margin.bottom;
		break;
	case SizeLock::width:
		Size.height = temp.height - Margin.bottom;
		break;
	case SizeLock::height:
		Size.width = temp.width - Margin.right;
		break;
	}
	Area::Draw(renderer);
}

Canvas::Canvas(Area *inParent)
{
	Position = location((*inParent).getPosition().x + 20, (*inParent).getPosition().y + 20);
	Size = size((*inParent).getSize().width - 40, (*inParent).getSize().height - 40);
	BackColour = colour(white);
	BorderColour = colour(white);
}

colour *Canvas::getCurrentColour()
{
	return &CurrentColour;
}

void Canvas::Fill(SDL_Renderer *renderer, SDL_Window *window, colour inColour, location mouseLocation, size CanvasSize, location CanvasPosition)
{
	colour plane[CanvasSize.width * CanvasSize.height];
	SDL_Surface *s = SDL_GetWindowSurface(window);
	SDL_ConvertSurfaceFormat(s, SDL_PIXELFORMAT_RGB24, 0);
	int y = 0;
	for (int x = 0; x < sizeof(s); x += 3)
	{
		if (x / 3 == (*s).w)
		{
			y++;
		}
		colour pcol;
		Uint32 pixel;
		SDL_Rect rect; /* SDL rectangle of 1 pixel */
		/* 2 helper structures to get SDL to generate the right pixel format */
		SDL_Surface *s = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);				/* helper 1 */
		SDL_Surface *ns = SDL_ConvertSurfaceFormat(s, SDL_PIXELFORMAT_ARGB8888, 0); /* 2 */
		rect.x = x;
		rect.y = y;
		rect.w = 1;
		rect.h = 1;
		/* renderer, pixel, target format, target array, safety value 5 (1 was needed) */
		if (!SDL_RenderReadPixels(renderer, &rect, SDL_PIXELFORMAT_ARGB8888, &pixel, 1))
		{ /* pixel, pixel format (from helper 2), colour channels by reference */
			SDL_GetRGB(pixel, ns->format, &(pcol.r), &(pcol.g), &(pcol.b));
		}
		SDL_FreeSurface(s);	 /* free helper 1 */
		SDL_FreeSurface(ns); /* free helper 2 */
		plane[x + (y * CanvasSize.width)] = pcol;
	}
	log("Fake canvas Created");
	SDL_SetRenderDrawColor(renderer, inColour.r, inColour.g, inColour.b, inColour.a);
	printf("Canvas Position x= %d y=%d\n", CanvasPosition.x, CanvasPosition.y);
	printf("Canvas Size x=%d y=%d\n", CanvasSize.width, CanvasSize.height);
	Fillr(renderer, mouseLocation, inColour, plane, &CanvasSize, &CanvasPosition);
}

void Canvas::Fillr(SDL_Renderer *renderer, location PointLocation, colour inColour, colour *plane, size *CanvasSize, location *CanvasPosition)
{
	printf("PointLocation x= %d, y= %d\n", PointLocation.x, PointLocation.y);
	printf("Canvas Colour %d %d %d\n", plane[PointLocation.x + (PointLocation.y * (*CanvasSize).width)].r, plane[PointLocation.x + (PointLocation.y * (*CanvasSize).width)].g, plane[PointLocation.x + (PointLocation.y * (*CanvasSize).width)].b);
	fflush(stdout);
	if (PointLocation.x < CanvasPosition->x || PointLocation.y < CanvasPosition->y || PointLocation.x > CanvasSize->width || PointLocation.y > CanvasSize->height)
	{
		log("Boundary Reached");
		return;
	}
	if (plane[PointLocation.x + (PointLocation.y * (*CanvasSize).width)].r != 0 || plane[PointLocation.x + (PointLocation.y * (*CanvasSize).width)].g != 0 || plane[PointLocation.x + (PointLocation.y * (*CanvasSize).width)].b != 0 || plane[PointLocation.x + (PointLocation.y * (*CanvasSize).width)].r != 255 || plane[PointLocation.x + (PointLocation.y * (*CanvasSize).width)].g != 255 || plane[PointLocation.x + (PointLocation.y * (*CanvasSize).width)].b != 255)
	{
		log("Colour Reached");
		return;
	}
	SDL_RenderDrawPoint(renderer, PointLocation.x, PointLocation.y);
	plane[PointLocation.x + (PointLocation.y * (*CanvasSize).width)] = inColour;
	Fillr(renderer, location(PointLocation.x - 1, PointLocation.y), inColour, plane, CanvasSize, CanvasPosition);
	// Fillr(renderer, location(PointLocation.x, PointLocation.y - 1), inColour, plane, CanvasSize, CanvasPosition);
	// Fillr(renderer, location(PointLocation.x + 1, PointLocation.y), inColour, plane, CanvasSize, CanvasPosition);
	// Fillr(renderer, location(PointLocation.x, PointLocation.y + 1), inColour, plane, CanvasSize, CanvasPosition);
	log("kernal complete");
}