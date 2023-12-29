#include "image.h"
#include "log.h"
#include "colour.h"

char *Image::getFilename()
{
    for (int i = sizeof(fullPath) / sizeof(char); i > 0; i--)
    {
        // Searches from the end of the path until the "/"
        if (fullPath[i] == *"/")
        {
            // Returns data on the right of the "/"
            char *filename = (char *)malloc((sizeof(fullPath) / sizeof(char)) - i);
            for (int j = i; j < sizeof(fullPath) / sizeof(char); j++)
            {
                filename[j - i] = fullPath[j];
            }
            return filename;
        }
    }
    return "NULL";
}

char *Image::getFileLocation()
{
    for (int i = sizeof(fullPath) / sizeof(char); i > 0; i--)
    {
        // Searches from the end of the path until the "/"
        if (fullPath[i] == *"/")
        {
            // Returns data on the left of the "/"
            char *path = (char *)malloc((sizeof(fullPath) / sizeof(char)) - i);
            for (int j = 0; j < i; j++)
            {
                path[j] = fullPath[j];
            }
            return path;
        }
    }
    return "NULL";
}
Image::Image(char *inFileLocation)
{
    // checks the extension
    if (inFileLocation[strlen(inFileLocation) - 3] == *"w" && inFileLocation[strlen(inFileLocation) - 3] == *"e" && inFileLocation[strlen(inFileLocation) - 2] == *"b" && inFileLocation[strlen(inFileLocation) - 1] == *"p")
    {
        ext = WEBP;
    }
    else if (inFileLocation[strlen(inFileLocation) - 3] == *"p" && inFileLocation[strlen(inFileLocation) - 2] == *"n" && inFileLocation[strlen(inFileLocation) - 1] == *"g")
    {
        ext = PNG;
    }
    else if (inFileLocation[strlen(inFileLocation) - 3] == *"j" && inFileLocation[strlen(inFileLocation) - 2] == *"p" && inFileLocation[strlen(inFileLocation) - 1] == *"g")
    {
        ext = JPG;
    }
    else if (inFileLocation[strlen(inFileLocation) - 3] == *"b" && inFileLocation[strlen(inFileLocation) - 2] == *"m" && inFileLocation[strlen(inFileLocation) - 1] == *"b")
    {
        ext = BMP;
    }
    else if (inFileLocation[strlen(inFileLocation) - 3] == *"t" && inFileLocation[strlen(inFileLocation) - 2] == *"i" && inFileLocation[strlen(inFileLocation) - 1] == *"f")
    {
        ext = TIF;
    }
    fullPath = inFileLocation;
}

Image::Image()
{
}

void Image::SaveImage(SDL_Renderer *renderer, SDL_Rect Canvas)
{
    // code based on "Eike Anderson" ref:3
    SDL_Surface *sectionSurface = SDL_CreateRGBSurface(0, Canvas.w, Canvas.h, 32, 0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);

    if (SDL_RenderReadPixels(renderer, &Canvas, SDL_PIXELFORMAT_RGBA8888, sectionSurface->pixels, sectionSurface->pitch) != 0)
    {
        log("Failed to read pixels from renderer");
        return;
    }

    switch (ext)
    {
    case JPG:
    {
        if (IMG_SaveJPG(sectionSurface, fullPath, 100) != 0)
        {
            log("Failed to save section as PNG image");
            return;
        }
    }
    break;
    default:
    {
        if (IMG_SavePNG(sectionSurface, fullPath) != 0)
        {
            log("Failed to save section as PNG image");
            return;
        }
    }
    }
    // end of code based on "Eike Anderson"
}

SDL_Surface *Image::getSurface()
{
    if (ImageData == nullptr)
    {
        ImageData = IMG_Load(fullPath);
    }
    return ImageData;
}

SDL_Texture *Image::getTexture(SDL_Renderer *renderer)
{
    return SDL_CreateTextureFromSurface(renderer, getSurface());
}

void Image::DrawImage(SDL_Renderer *renderer, SDL_Rect Canvas)
{
    SDL_Texture *temp = getTexture(renderer);
    SDL_SetTextureBlendMode(temp, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(temp, 255);
    SDL_SetTextureColorMod(temp, 255, 255, 255);
    SDL_RenderCopy(renderer, temp, NULL, &Canvas);
    SDL_RenderPresent(renderer);
}

imageExtention Image::getExt()
{
    return ext;
}

size Image::getImageSize()
{
    return size(getSurface()->w, getSurface()->h);
}