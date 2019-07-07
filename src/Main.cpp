// Main.cpp : Defines the entry point for the console application.
//
#include "SandPile.hpp"
#include <SDL2/SDL.h>
#include "ScreenBuffer.hpp"
#include <iostream>
#include <string>
#include <thread>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void updateScreen(SandPile* p, SDL_Renderer* renderer, ScreenBuffer* screenBuffer);
static void placeSandStatic(SandPile* p, size_t x, size_t y, size_t amount);

int main(int argc, char* args[])
{
	//Initialize SDL window and renderer for viewing fractal
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return 1;

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
	/*
	std::cout << "Wait until pile settles to render? (y/n): ";
	std::cin >> toSettle;

	bool waitToSettle = tolower(toSettle) == 'y' ? true : false;
	*/


	SDL_Window *window = SDL_CreateWindow("Sand Pile", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	ScreenBuffer* screenBuffer = new ScreenBuffer((size_t)SCREEN_WIDTH, (size_t)SCREEN_HEIGHT);
	SDL_Event event;
	SDL_RenderSetScale(renderer, renderScale, renderScale);
	bool running = true;

	int placeX = SCREEN_WIDTH / 2 / renderScale;
	int placeY = SCREEN_HEIGHT / 2 / renderScale;

	//TODO: Set boolean or just delete
	SandPile* p = new SandPile(SCREEN_WIDTH, SCREEN_HEIGHT, threshold, true, renderer, screenBuffer);
	std::thread thread (placeSandStatic, p, placeX, placeY, sandToPlace);

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
					p->randomizeColors();
					break;
				case SDLK_ESCAPE:
					running = false;
					break;
				}						
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				SDL_GetMouseState(&placeX, &placeY);
				placeX /= renderScale; placeY /= renderScale;
			}
		}
		updateScreen(p, renderer, screenBuffer);
	}

	//Free memory
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

void updateScreen(SandPile* p, SDL_Renderer* renderer, ScreenBuffer* screenBuffer)
{
	struct Pixel** pixels = screenBuffer->getPixels();
	for(int i = 0; i < SCREEN_WIDTH; i++)
	{
		for(int j = 0; j < SCREEN_HEIGHT; j++)
		{
			if(pixels[i][j].a != 0)
			{
				struct Pixel* pixel = &pixels[i][j];
				SDL_SetRenderDrawColor(renderer, pixel->r, pixel->g, pixel->b, pixel->a);
				SDL_RenderDrawPoint(renderer, i, j);
			}
		}
	}
	SDL_RenderPresent(renderer);
}

static void placeSandStatic(SandPile* p, size_t x, size_t y, size_t amount)
{
	while(true)
		p->placeSand(x, y, amount);
}