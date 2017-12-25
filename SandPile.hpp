#pragma once
#include <stdio.h>
#include <stack>
#include "Point.hpp"
#include "ScreenBuffer.hpp"
#include <vector>
#include <SDL2/SDL.h>
#include <map>
#include <time.h>
#include <iostream>


class SandPile
{
public:
	SandPile(size_t width, size_t height, size_t threshold, bool waitToSettle, SDL_Renderer *renderer, ScreenBuffer* screenBuffer);
	~SandPile();

	size_t getWidth();
	size_t getHeight();
	int placeSand(size_t x, size_t y, size_t amount);
	void printBoard();
	void randomizeColors();
	size_t** getPile();
	size_t **pile;
	void setPlacementParams(size_t x, size_t y, size_t amount);
	void runSDLThread();
	ScreenBuffer* screenBuffer;
	size_t placeX, placeY, amount;

private:
	std::vector<Point> getPossibleAdjacentPoints(size_t x, size_t y);
	int** generateColorPointer();
	void drawToScreenBuffer(Point p);
	SDL_Thread* thread;
	bool waitToSettle;
	std::stack<Point> toCheck;
	int** colors;
	size_t width, height, threshold;
	SDL_Renderer *renderer;

protected:
};

