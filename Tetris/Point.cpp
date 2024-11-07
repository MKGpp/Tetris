#include <iostream>
#include <string>
#include "Point.h"

Point::Point() : x(0), y(0)
{
}

Point::Point(int x, int y) : x(x), y(y) {}

void Point::setX(const int x)
{
	this->x = x;
}

void Point::setY(const int y)
{
	this->y = y;
}

void Point::setXY(const int x, const int y)
{
	this->x = x;
	this->y = y;
}

void Point::swapXY()
{
	std::swap(x, y);
}

void Point::multiplyX(const int& factor)
{
	x *= factor;
}

void Point::multiplyY(const int& factor)
{
	y *= factor;
}

std::string Point::toString() const
{
	return "[" + std::to_string(x) +"," + std::to_string(y) + "]";
}
