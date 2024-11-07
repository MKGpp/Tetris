#include "Gameboard.h"
#include "Point.h"
#include <iostream>
#include <iomanip>
#include <cassert>

Gameboard::Gameboard() {
	empty();
}

void Gameboard::empty()
{
	for (int i = 0; i < MAX_Y; i++) {
		fillRow(i, EMPTY_BLOCK);
	}
}

void Gameboard::printToConsole() const
{
	for (int row = 0; row < MAX_Y; row++) {
		for (int col = 0; col < MAX_X; col++) {
			int content = grid[row][col];
			if (content == EMPTY_BLOCK) {
				std::cout << std::setw(2) << '.';
			}
			else {
				std::cout << std::setw(2) << content;
			}
		}
		std::cout << '\n';
	}
}

int Gameboard::getContent(const Point& p) const
{
	assert(isValidPoint(p));
	return grid[p.getY()][p.getX()];
}

int Gameboard::getContent(int x, int y) const
{
	assert(isValidPoint(x, y));
	return grid[y][x];
}

void Gameboard::setContent(const Point& p, int content)
{
	if (isValidPoint(p)) {
		grid[p.getY()][p.getX()] = content;
	}
}

void Gameboard::setContent(int col, int row, int content)
{
	if (isValidPoint(col, row)) {
		grid[row][col] = content;
	}
}

void Gameboard::setContent(const std::vector<Point>& points, int content)
{
	for (const Point& point : points) {
		if (isValidPoint(point)) {
			grid[point.getY()][point.getX()] = content;
		}
	}
}

bool Gameboard::areAllLocsEmpty(const std::vector<Point>& locs) const
{
	for (const Point& loc : locs) {
		if (isValidPoint(loc)) {
			if (getContent(loc) != EMPTY_BLOCK) {
				return false;
			}
		}
	}
	return true;
}

int Gameboard::removeCompletedRows()
{
	std::vector<int> rowsToRemove;
	rowsToRemove = getCompletedRowIndices();
	removeRows(rowsToRemove);
	return static_cast<int>(rowsToRemove.size());
}

bool Gameboard::isValidPoint(const Point& p) const
{
	return (p.getX() >= 0 && p.getX() < MAX_X && p.getY() >= 0 && p.getY() < MAX_Y);
}

bool Gameboard::isValidPoint(int x, int y) const
{
	return (x >= 0 && x < MAX_X && y >= 0 && y < MAX_Y);
}

bool Gameboard::isRowCompleted(int rowIndex) const
{
	assert(rowIndex >= 0 && rowIndex < MAX_Y);
	for (int col = 0; col < MAX_X; col++) {
		if (grid[rowIndex][col] == EMPTY_BLOCK) {
			return false;
		}
	}
	return true;
}

void Gameboard::fillRow(int rowIndex, int content)
{
	for (int i = 0; i < MAX_X; i++) {
		grid[rowIndex][i] = content;
	}
}

std::vector<int> Gameboard::getCompletedRowIndices() const
{
	std::vector<int> rowIndices;
	for (int i = 0; i < MAX_Y; i++)
	{
		if (isRowCompleted(i)) {
			rowIndices.push_back(i);
		}
	}
	return rowIndices;
}

void Gameboard::copyRowIntoRow(int source, int target)
{
	for (int i = 0; i < MAX_X; i++) {
		grid[target][i] = grid[source][i];
	}
}

void Gameboard::removeRow(int rowIndex)
{
	assert(rowIndex >= 0 && rowIndex < MAX_Y);
	if (rowIndex >= 0 && rowIndex < MAX_Y) {
		for (int i = rowIndex-1; i >= 0; i--)
		{
			copyRowIntoRow(i, i + 1);
		}
		fillRow(0, EMPTY_BLOCK);
	}
}

void Gameboard::removeRows(const std::vector<int>& rows)
{
	for (const int& row : rows) {
		removeRow(row);
	}
}
