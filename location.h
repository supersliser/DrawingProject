#pragma once
class location
{
public:
    int x;
    int y;
    location();
    location(int in);
    location(int inX, int inY);
    location Add(location in);
};

class size
{
public:
    int width;
    int height;
    size();
    size(int in);
    size(int inWidth, int inHeight);
};

class margin
{
public:
    int top;
    int bottom;
    int left;
    int right;
    margin();
    margin(int inT, int inB, int inL, int inR);
    margin(location inLoc);
};

enum SizeLock
{
    none = 0,
    width,
    height,
    all
};