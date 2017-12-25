#pragma once
class Point
{
public:
	Point(int x, int y);
	~Point();

	int getX();
	int getY();

private:
	int x, y;
};

