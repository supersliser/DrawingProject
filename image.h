#pragma once
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "location.h"
enum imageExtention
{
    BMP = 0,
    PNG,
    TIF,
    JPG,
    WEBP
};

class Image
{
protected:
    char *fullPath;
    imageExtention ext;
    char *getFilename();
    char *getFileLocation();
    SDL_Surface *ImageData = nullptr;

public:
    Image();
    imageExtention getExt();
    Image(char *inFileLocation);
    SDL_Surface *getSurface();
    SDL_Texture *getTexture(SDL_Renderer *renderer);
    void DrawImage(SDL_Renderer *renderer, SDL_Rect Canvas);
    void SaveImage(SDL_Renderer *renderer, SDL_Rect Canvas);
    size getImageSize();
};