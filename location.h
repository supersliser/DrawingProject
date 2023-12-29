#pragma once

//stores an x y coordinate where the origin is the top left
class location
{
public:
//the horizontal coordinate
    int x;
//the vertical coordinate
    int y;
    //constructor
    location();
    location(int in);
    location(int inX, int inY);
    //adds a location to another location
    location Add(location in);
};

//stores an x y coordinate as a size
class size
{
public:
//the horizontal size
    int width;
//the vertical size
    int height;
//constructors
    size();
    size(int in);
    size(int inWidth, int inHeight);
};