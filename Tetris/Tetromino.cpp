#include <iostream>
#include <vector>
#include "Tetromino.h"
#include "Point.h"
#include <random>


Tetromino::Tetromino()
{
	setShape(TetShape::O);
}

TetColor Tetromino::getColor() const
{
	return color;
}

TetShape Tetromino::getShape() const
{
	return shape;
}

void Tetromino::setShape(TetShape shape)
{
	switch (shape)
	{
	case TetShape::S:
		blockLocs = {Point(0,0), Point(-1,0), Point(0,1), Point(1,1)};
		color = TetColor::RED;
		break;
	case TetShape::Z:
		blockLocs = { Point(-1,1), Point(0,1), Point(0,0), Point(1,0) };
		color = TetColor::GREEN;
		break;
	case TetShape::L:
		blockLocs = { Point(0,1), Point(0,0), Point(0,-1), Point(1,-1) };
		color = TetColor::ORANGE;
		break;
	case TetShape::J:
		blockLocs = { Point(-1,-1), Point(0,-1), Point(0,0), Point(0,1) };
		color = TetColor::BLUE_DARK;
		break;
	case TetShape::O:
		blockLocs = { Point(0,0), Point(0,1), Point(1,1), Point(1,0) };
		color = TetColor::YELLOW;
		break;
	case TetShape::I:
		blockLocs = { Point(0,-1), Point(0,0), Point(0,1), Point(0,2) };
		color = TetColor::BLUE_LIGHT;
		break;
	case TetShape::T:
		blockLocs = { Point(-1,0), Point(0,0), Point(1,0), Point(0,-1) };
		color = TetColor::PURPLE;
		break;
	default:
		break;
	}
}

void Tetromino::rotateClockwise()
{
	if (color == TetColor::YELLOW) { return; }
	for (auto& block : blockLocs)
	{
		block.swapXY();
		block.multiplyY(-1);
	}
}

void Tetromino::printToConsole() const
{
	const int gridMin = -3;
	const int gridMax = 3; 

	for (int y = gridMax; y > gridMin; --y)
	{
		for (int x = gridMin; x < gridMax; ++x)
		{
			bool found = false;
			for (const auto& block : blockLocs) {
				if (block.getX() == x && block.getY() == y) {
					found = true;
					break;
				}
			}
			if (found) {
				std::cout << "x";
			}
			else {
				std::cout << ".";
			}
		}
		
		std::cout << '\n';
	}
}

TetShape Tetromino::getRandomShape()
{
	int randShape = rand() % static_cast<int>(TetShape::count);
	return static_cast<TetShape>(randShape);
}


