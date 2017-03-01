#pragma once
#include <stdio.h>
#include <stack>
#include "Point.h"
#include <vector>
#include <SDL.h>
#include <map>
#include <time.h>
#include <iostream>


class SandPile
{
public:
	SandPile(size_t width, size_t height, size_t threshold, bool waitToSettle, SDL_Renderer *renderer);
	~SandPile();

	size_t getWidth();
	size_t getHeight();
	void placeSandAndRender(size_t x, size_t y, size_t amount);
	void createWall(Point p1, Point p2);
	void printBoard();
	void randomizeColors();
	int** getPile();
	int **pile;

private:
	std::vector<Point> getPossibleAdjacentPoints(size_t x, size_t y);
	int** generateColorPointer();
	void drawPoint(SDL_Renderer *renderer, Point p);

	bool waitToSettle;
	std::stack<Point> toCheck;
	int** colors;
	SDL_Renderer *renderer;
	size_t width, height, threshold;
};

