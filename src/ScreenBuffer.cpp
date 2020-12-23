#include "ScreenBuffer.hpp"

ScreenBuffer::ScreenBuffer(size_t width, size_t height)
{
    this->width = width;
    this->height = height;

    this->pixels = new struct Pixel*[width];

    for(size_t i = 0; i < width; i++)
    {
        this->pixels[i] = new struct Pixel[height];

        for(size_t j = 0; j < height; j++)
        {
            //To know which to draw, alpha starts at 0
            pixels[i][j].a = 0;
        }
        
    }
}

void ScreenBuffer::setPixel(size_t x, size_t y, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    struct Pixel* p = &this->pixels[x][y];
    p->r = r; 
    p->g = g;
    p->b = b;
    p->a = a;
}

size_t ScreenBuffer::getWidth()
{
    return this->width;
}

size_t ScreenBuffer::getHeight()
{
    return this->height;
}

struct Pixel** ScreenBuffer::getPixels()
{
    return this->pixels;
}
