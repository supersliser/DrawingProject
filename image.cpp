#include "image.h"

char *Image::getFilename()
{
    for (int i = sizeof(fullPath) / sizeof(char); i > 0; i--)
    {
        if (fullPath[i] == *"/")
        {
            char *filename = (char *)malloc((sizeof(fullPath) / sizeof(char)) - i);
            for (int j = i; j < sizeof(fullPath) / sizeof(char); j++)
            {
                filename[j - i] = fullPath[j];
            }
            return filename;
        }
    }
}

char *Image::getFileLocation()
{
    for (int i = sizeof(fullPath) / sizeof(char); i > 0; i--)
    {
        if (fullPath[i] == *"/")
        {
            char *path = (char *)malloc((sizeof(fullPath) / sizeof(char)) - i);
            for (int j = 0; j < i; j++)
            {
                path[j] = fullPath[j];
            }
            return path;
        }
    }
}

Image::Image()
{
}
Image::Image(char *inFileLocation)
{
    if (inFileLocation[sizeof(inFileLocation) / sizeof(char) - 3] == *"w" && inFileLocation[sizeof(inFileLocation) / sizeof(char) - 3] == *"e" && inFileLocation[sizeof(inFileLocation) / sizeof(char) - 2] == *"b" && inFileLocation[sizeof(inFileLocation) / sizeof(char) - 1] == *"p")
    {
        ext = WEBP;
    }
    else if (inFileLocation[sizeof(inFileLocation) / sizeof(char) - 3] == *"p" && inFileLocation[sizeof(inFileLocation) / sizeof(char) - 2] == *"n" && inFileLocation[sizeof(inFileLocation) / sizeof(char) - 1] == *"g")
    {
        ext = PNG;
    }
    else if (inFileLocation[sizeof(inFileLocation) / sizeof(char) - 3] == *"j" && inFileLocation[sizeof(inFileLocation) / sizeof(char) - 2] == *"p" && inFileLocation[sizeof(inFileLocation) / sizeof(char) - 1] == *"g")
    {
        ext = JPG;
    }
    else if (inFileLocation[sizeof(inFileLocation) / sizeof(char) - 3] == *"b" && inFileLocation[sizeof(inFileLocation) / sizeof(char) - 2] == *"m" && inFileLocation[sizeof(inFileLocation) / sizeof(char) - 1] == *"b")
    {
        ext = BMP;
    }
    else if (inFileLocation[sizeof(inFileLocation) / sizeof(char) - 3] == *"t" && inFileLocation[sizeof(inFileLocation) / sizeof(char) - 2] == *"i" && inFileLocation[sizeof(inFileLocation) / sizeof(char) - 1] == *"f")
    {
        ext = TIF;
    }
    fullPath = inFileLocation;
}

SDL_Surface *Image::getSurface()
{
    return IMG_Load(fullPath);
}

SDL_Texture *Image::getTexture(SDL_Renderer *renderer)
{
    return SDL_CreateTextureFromSurface(renderer, getSurface());
}

void Image::DrawImage(SDL_Renderer *renderer, SDL_Rect *Canvas)
{
    SDL_RenderCopy(renderer, getTexture(renderer), NULL, Canvas);
}