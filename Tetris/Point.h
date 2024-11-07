#ifndef POINT_H
#define POINT_H

#include <string>

class Point
{
public:
	Point();
	Point(int x, int y);

	int getX() const { return x; }
	int getY() const { return y; }

	void setX(const int x);
	void setY(const int y);
	void setXY(const int x, const int y);

	void swapXY();
	void multiplyX(const int& factor);
	void multiplyY(const int& factor);

	std::string toString() const;

private:
	int x;
	int y;
};

#endif // !POINT_H

