#pragma once
#include <stdio.h>

class ScreenBuffer
{
public:
	ScreenBuffer(size_t width, size_t height);
	~ScreenBuffer();

	size_t getWidth();
	size_t getHeight();
	void setPixel(size_t x, size_t y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    struct Pixel** getPixels();

private:
    size_t width, height;
    struct Pixel** pixels;

};

struct Pixel
{
	unsigned char r, g, b, a;
};

