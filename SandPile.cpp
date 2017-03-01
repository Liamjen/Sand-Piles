#include "SandPile.h"

SandPile::SandPile(size_t width, size_t height, size_t threshold, bool waitToSettle, SDL_Renderer *renderer)
{
	this->height = height;
	this->width = width;	
	this->threshold = threshold;
	this->waitToSettle = waitToSettle;
	this->renderer = renderer;
	pile = new int*[width];
	for (size_t i = 0; i < width; i++)
	{
		pile[i] = new int[height];
	}

	for (size_t i = 0; i < width; i++)
		for (size_t j = 0; j < height; j++)
			pile[i][j] = 0;

	srand((unsigned int)time(NULL));
	this->colors = generateColorPointer();
}

void SandPile::placeSandAndRender(size_t x, size_t y, size_t amount)
{
	pile[x][y] += amount;

	toCheck.push(Point(x, y));

	while (!toCheck.empty())
	{
		Point current = toCheck.top();

		if (pile[current.getX()][current.getY()] >= threshold)
		{
			std::vector<Point> possibleAdjacentPoints = getPossibleAdjacentPoints(current.getX(), current.getY());

			size_t divThreshold = pile[current.getX()][current.getY()] / threshold;

			for (size_t i = 0; i < possibleAdjacentPoints.size(); i++)
			{
				pile[possibleAdjacentPoints[i].getX()][possibleAdjacentPoints[i].getY()] += divThreshold;
			}
			pile[current.getX()][current.getY()] -= (divThreshold * threshold);

			drawPoint(renderer, current);
			if (!waitToSettle)
				SDL_RenderPresent(renderer);

			toCheck.pop();
			for (size_t i = 0; i < possibleAdjacentPoints.size(); i++)
				toCheck.push(possibleAdjacentPoints[i]);
		}
		else
		{
			drawPoint(renderer, current);
			if (!waitToSettle)
				SDL_RenderPresent(renderer);
			toCheck.pop();
		}
	}
	if (waitToSettle)
	{
		SDL_RenderPresent(renderer);
	}
}

void SandPile::createWall(Point p1, Point p2)
{
	int rise = p1.y - p2.y;
	int run = p1.x - p2.x;
	std::cout << "rise: " << rise << "\n";
	std::cout << "run: " << rise << "\n";

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	for (int i = 0; i < run; i++)
		for (int j = 0; j < rise; j++)
		{
			pile[i][j] = -1;
		}
	SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
	SDL_RenderPresent(renderer);
}

void SandPile::drawPoint(SDL_Renderer *renderer, Point p)
{
	size_t sandVal = pile[p.getX()][p.getY()];
	SDL_SetRenderDrawColor(renderer, colors[sandVal][0], colors[sandVal][1], colors[sandVal][2], 255);
	SDL_RenderDrawPoint(renderer, p.getX(), p.getY());
}

int** SandPile::generateColorPointer()
{
	int** colors = (int**)(malloc(threshold * sizeof(int)));
	colors[0] = (int*)(malloc(3 * sizeof(int)));
	colors[0][0] = 0; colors[0][1] = 0; colors[0][2] = 0;
	for (size_t i = 1; i < threshold; i++)
	{
		colors[i] = (int*)(malloc(3 * sizeof(int)));
		for (size_t j = 0; j < 3; j++)
			colors[i][j] = rand() % 255;
	}
	return colors;
}

void SandPile::randomizeColors()
{
	free(colors);
	colors = generateColorPointer();
}

void SandPile::printBoard()
{
	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
			printf("%zu", pile[i][j]);
		printf("\n");
	}
}

std::vector<Point> SandPile::getPossibleAdjacentPoints(size_t x, size_t y)
{
	std::vector<Point> v;

	if (x > 0)
		v.push_back(Point(x - 1, y));
	if (y > 0)
		v.push_back(Point(x, y - 1));
	if (x < width - 1)
		v.push_back(Point(x + 1, y));
	if (y < height - 1)
		v.push_back(Point(x, y + 1));

	return v;
}

int** SandPile::getPile()
{
	return pile;
}

size_t SandPile::getHeight()
{
	return height;
}

size_t SandPile::getWidth()
{
	return width;
}


SandPile::~SandPile()
{
	delete(pile);
	delete(colors);
}
