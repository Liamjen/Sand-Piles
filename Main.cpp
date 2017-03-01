// Main.cpp : Defines the entry point for the console application.
//
#include "SandPile.h"
#include <SDL.h>
#include <iostream>
#include <string>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(int argc, char* args[])
{
	//Initialize SDL window and renderer for viewing fractal
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		printf("%s", SDL_GetError);

	size_t renderScale = 4;
	size_t threshold = 4;
	size_t sandToPlace = 1;
	char toSettle = 'y';

	std::cout << "Enter pixel scale (Default = 4): ";
	std::cin >> renderScale;
	std::cout << "Enter sand topple threshold (Default = 4): ";
	std::cin >> threshold;
	std::cout << "Enter amount of sand to drop per iteration (Default = 1): ";
	std::cin >> sandToPlace;
	std::cout << "Wait until pile settles to render? (y/n): ";
	std::cin >> toSettle;

	bool creatingWalls = true;
	bool waitToSettle = tolower(toSettle) == 'y' ? true : false;


	SDL_Window *window = SDL_CreateWindow("Sand Pile", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_Event event;
	SDL_RenderSetScale(renderer, renderScale, renderScale);
	bool running = true;

	SandPile p(SCREEN_WIDTH, SCREEN_HEIGHT, threshold, waitToSettle, renderer);

	int placeX = SCREEN_WIDTH / 2 / renderScale;
	int placeY = SCREEN_HEIGHT / 2 / renderScale;

	Point p1(0, 0);
	Point p2(0, 0);

	SDL_RenderPresent(renderer);

	/*
	Main SDL loop
	*/
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = false;
			else if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
				case SDLK_r:
					p.randomizeColors();
					break;
				case SDLK_w:
					creatingWalls = false;
				case SDLK_ESCAPE:
					running = false;
					break;
				}						
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (creatingWalls)
					SDL_GetMouseState(&p1.x, &p1.y);
				else
				{
					SDL_GetMouseState(&placeX, &placeY);
					placeX /= renderScale; placeY /= renderScale;
				}
			}
			else if (event.type == SDL_MOUSEBUTTONUP)
			{
				if (creatingWalls)
				{
					SDL_GetMouseState(&p2.x, &p2.y);
					p.createWall(p1, p2);
				}
			}
		}

		if(!creatingWalls)
			p.placeSandAndRender(placeX, placeY, sandToPlace);
	}

	//Free memory
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

