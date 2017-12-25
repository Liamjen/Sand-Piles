#include "SandPile.hpp"

SandPile::SandPile(size_t width, size_t height, size_t threshold, bool waitToSettle, SDL_Renderer *renderer, ScreenBuffer* screenBuffer)
{
	this->height = height;
	this->width = width;	
	this->threshold = threshold;
	this->waitToSettle = waitToSettle;
	this->renderer = renderer;
	this->thread = NULL;
	this->pile = new size_t*[this->width];
	this->screenBuffer = screenBuffer;
	for (size_t i = 0; i < this->width; i++)
	{
		this->pile[i] = new size_t[this->height];
	}

	for (size_t i = 0; i < this->width; i++)
		for (size_t j = 0; j < this->height; j++)
			this->pile[i][j] = 0;

	srand((unsigned int)time(NULL));
	this->colors = this->generateColorPointer();
}

int SandPile::placeSand(size_t x, size_t y, size_t amount)
{
	this->pile[x][y] += amount;

	this->toCheck.push(Point(x, y));

	while (!(this->toCheck.empty()))
	{
		Point current = this->toCheck.top();

		if (this->pile[current.getX()][current.getY()] >= this->threshold)
		{
			std::vector<Point> possibleAdjacentPoints = this->getPossibleAdjacentPoints(current.getX(), current.getY());

			size_t divThreshold = this->pile[current.getX()][current.getY()] / this->threshold;

			for (size_t i = 0; i < possibleAdjacentPoints.size(); i++)
			{
				this->pile[possibleAdjacentPoints[i].getX()][possibleAdjacentPoints[i].getY()] += divThreshold;
			}
			this->pile[current.getX()][current.getY()] -= (divThreshold * this->threshold);

			this->drawToScreenBuffer(current);

			this->toCheck.pop();
			for (size_t i = 0; i < possibleAdjacentPoints.size(); i++)
				this->toCheck.push(possibleAdjacentPoints[i]);
		}
		else
		{
			this->drawToScreenBuffer(current);
			/*
			if (!this->waitToSettle)
				SDL_RenderPresent(this->renderer);
				*/
			this->toCheck.pop();
		}
	}
	/*
	if (this->waitToSettle)
	{
		SDL_RenderPresent(this->renderer);
	}*/

	return true;
}

void SandPile::drawToScreenBuffer(Point p)
{
	size_t sandVal = pile[p.getX()][p.getY()];
	this->screenBuffer->setPixel(p.getX(), p.getY(), this->colors[sandVal][0], 
													 this->colors[sandVal][1], 
													 this->colors[sandVal][2], 255);
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
	this->colors = this->generateColorPointer();
}

void SandPile::printBoard()
{
	for (size_t i = 0; i < this->width; i++)
	{
		for (size_t j = 0; j < this->height; j++)
			printf("%zu", this->pile[i][j]);
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

size_t** SandPile::getPile()
{
	return this->pile;
}

size_t SandPile::getHeight()
{
	return this->height;
}

size_t SandPile::getWidth()
{
	return this->width;
}


SandPile::~SandPile()
{
	delete(this->pile);
	delete(this->colors);
}
