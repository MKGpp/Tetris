#ifndef TETROMINO_H
#define TETROMINO_H
#include <vector>
#include "Point.h"

enum class TetColor
{
	RED,
	ORANGE,
	YELLOW,
	GREEN,
	BLUE_LIGHT,
	BLUE_DARK,
	PURPLE,
};

enum class TetShape
{
	S,
	Z,
	L,
	J,
	O,
	I,
	T,
	count,
};

class Tetromino
{
	friend class TestSuite;
	friend class GridTetromino;
public:
	Tetromino();
	TetColor getColor() const;
	TetShape getShape() const;

	void setShape(TetShape shape);
	void rotateClockwise();
	void printToConsole() const;
	static TetShape getRandomShape();

private:
	TetColor color;
	TetShape shape;
	std::vector<Point> blockLocs;
};

#endif // !TETROMINO_H
