
#include "Point.hpp"


Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}

int Point::getX()
{
	return this->x;
}

int Point::getY()
{
	return this->y;
}

Point::~Point()
{

}
