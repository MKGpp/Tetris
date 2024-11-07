#include "GridTetromino.h"

void GridTetromino::setGridLoc(int x, int y)
{
	gridLoc.setXY(x, y);
}

void GridTetromino::setGridLoc(const Point& newGridLoc)
{
	gridLoc = newGridLoc;
}

void GridTetromino::move(int xOffset, int yOffset)
{
	gridLoc.setX(gridLoc.getX() + xOffset);
	gridLoc.setY(gridLoc.getY() + yOffset);
}

std::vector<Point> GridTetromino::getBlockLocsMappedToGrid() const
{
	std::vector<Point> blockLocToMap;
	for (const auto& loc : blockLocs) {
		int mappedX = gridLoc.getX() + loc.getX();
		int mappedY = gridLoc.getY() + loc.getY();
		blockLocToMap.emplace_back(mappedX, mappedY);
	}
	return blockLocToMap;
}
