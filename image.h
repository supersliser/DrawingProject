#pragma once
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "location.h"

// The types of file extension supported by the program
enum imageExtention
{
    BMP = 0,
    PNG,
    TIF,
    JPG,
    WEBP
};

// Stores an image and allows access to secondary storage
class Image
{
protected:
    // The relative or direct path to the image
    char *fullPath;
    // The extension of the image
    imageExtention ext;
    // gets the filename part of the path
    char *getFilename();
    // gets the location of the file
    char *getFileLocation();
    SDL_Surface *ImageData = nullptr;

public:
    // constructor
    Image();
    Image(char *inFileLocation);
    // getters
    imageExtention getExt();
    SDL_Surface *getSurface();
    SDL_Texture *getTexture(SDL_Renderer *renderer);
    size getImageSize();
    // Draws the image to the canvas
    void DrawImage(SDL_Renderer *renderer, SDL_Rect Canvas);
    // Saves the image to secondary storage
    void SaveImage(SDL_Renderer *renderer, SDL_Rect Canvas);
};