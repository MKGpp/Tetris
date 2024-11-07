#include "TetrisGame.h"
#include <iostream>
#include <cassert>

const int TetrisGame::BLOCK_WIDTH = 32;
const int TetrisGame::BLOCK_HEIGHT = 32;
const double TetrisGame::MAX_SECONDS_PER_TICK = 0.75;
const double TetrisGame::MIN_SECONDS_PER_TICK = 0.20;

TetrisGame::TetrisGame(sf::RenderWindow& window, sf::Sprite& blockSprite, const Point& gameboardOffset, const Point& nextShapeOffset) :
	window(window),
	blockSprite(blockSprite),
	gameboardOffset(gameboardOffset),
	nextShapeOffset(nextShapeOffset)
{
	reset();
	if (!scoreFont.loadFromFile("fonts/RedOctober.ttf")) {
		assert(false && "Missing font: RedOctober.ttf");
	}
	scoreText.setFont(scoreFont);
	scoreText.setCharacterSize(18);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(425, 325);
}

void TetrisGame::draw()
{	
	drawGameboard();
	drawTetromino(currentShape, gameboardOffset);
	drawTetromino(nextShape, nextShapeOffset);
	window.draw(scoreText);

}

void TetrisGame::onKeyPressed(const sf::Event& event)
{
	switch (event.key.code)
	{
		case sf::Keyboard::Up:
			attemptRotate(currentShape);
			break;
		case sf::Keyboard::Left:
			attemptMove(currentShape,-1,0);
			break;
		case sf::Keyboard::Right:
			attemptMove(currentShape,1,0);
			break;
		case sf::Keyboard::Down:
			if (!attemptMove(currentShape, 0, 1)) { lock(currentShape); }
			break;
		case sf::Keyboard::Space:
			drop(currentShape);
			lock(currentShape);
		default:
			break;
	}
}

void TetrisGame::processGameLoop(float secondsSinceLastLoop)
{
	secondsSinceLastTick += secondsSinceLastLoop;

	while (secondsSinceLastTick >= secondsPerTick) {
		tick();
		secondsSinceLastTick -= secondsPerTick;
	}

	if (shapePlacedSinceLastGameLoop) {
		shapePlacedSinceLastGameLoop = false;
		if (spawnNextShape()) {
			pickNextShape();
			switch (board.removeCompletedRows())
			{
			case 1:
				score += 100;
				break;
			case 2:
				score += 300;
				break;
			case 3:
				score += 500;
				break;
			case 4:
				score += 800;
				break;
			default:
				break;
			}
			updateScoreDisplay();
			determineSecondsPerTick();
		}
		else {
			reset();
		}
	}
}

void TetrisGame::tick()
{
	if (!attemptMove(currentShape, 0, 1)) {
		lock(currentShape);
	}
}

void TetrisGame::reset()
{
	score = 0;
	updateScoreDisplay();

	determineSecondsPerTick();

	board.empty();

	pickNextShape();
	spawnNextShape();

	pickNextShape();
}

void TetrisGame::pickNextShape()
{
	nextShape.setShape(getRandomShape());
}

bool TetrisGame::spawnNextShape()
{
	currentShape = nextShape;

	Point spawnLoc = board.getSpawnLoc();
	currentShape.setGridLoc(spawnLoc);

	return isPositionLegal(currentShape);
}

bool TetrisGame::attemptRotate(GridTetromino& shape)
{
	GridTetromino temp = shape;
	temp.rotateClockwise();
	if (isPositionLegal(temp)) {
		shape.rotateClockwise();
		return true;
	}
	return false;
}

bool TetrisGame::attemptMove(GridTetromino& shape, int x, int y)
{
	GridTetromino temp = shape;
	temp.move(x,y);

	if (isPositionLegal(temp)) {
		shape.move(x, y);
		return true;
	}
	return false;
}

void TetrisGame::drop(GridTetromino& shape)
{
	while (attemptMove(shape, 0,1)) {}
}

void TetrisGame::lock(const GridTetromino& shape)
{
	auto mappedLocs = shape.getBlockLocsMappedToGrid();

	for (const auto& loc : mappedLocs) {
		int x = loc.getX();
		int y = loc.getY();
		board.setContent(x, y, static_cast<int>(shape.getColor()));
	}
	shapePlacedSinceLastGameLoop = true;
}


void TetrisGame::drawBlock(const Point& topLeft, int xOffset, int yOffset, const TetColor& color)
{
	int pixelX = topLeft.getX() + xOffset * BLOCK_WIDTH;
	int pixelY = topLeft.getY() + yOffset * BLOCK_HEIGHT;

	int colorIndex = static_cast<int>(color);
	int row = colorIndex / 8;
	int col = colorIndex % 8;
	
	blockSprite.setTextureRect(sf::IntRect(col * BLOCK_WIDTH, row * BLOCK_HEIGHT, BLOCK_WIDTH, BLOCK_HEIGHT));
	blockSprite.setPosition(static_cast<float>(pixelX), static_cast<float>(pixelY));
	window.draw(blockSprite);
}

void TetrisGame::drawGameboard()
{
	Point boardTopLeft(gameboardOffset);

	for (int y = 0; y < Gameboard::MAX_Y; y++)
	{
		for (int x = 0; x < Gameboard::MAX_X; x++)
		{
			int content = board.getContent(x, y);
			if (content != Gameboard::EMPTY_BLOCK) {
				drawBlock(boardTopLeft, x, y, static_cast<TetColor>(content));
			}
		}
	}

}

void TetrisGame::drawTetromino(const GridTetromino& t, const Point& topLeft)
{
	for (const auto& block : t.getBlockLocsMappedToGrid()) {
		drawBlock(topLeft, block.getX(), block.getY(), t.getColor());
	}
}

void TetrisGame::updateScoreDisplay()
{
	std::string scoreString = "score: " + std::to_string(score);
	scoreText.setString(scoreString);
}

bool TetrisGame::isPositionLegal(const GridTetromino& shape) const
{
	if (isWithinBorders(shape)) {
		return board.areAllLocsEmpty(shape.getBlockLocsMappedToGrid());
	}
	
	return false;

}

bool TetrisGame::isWithinBorders(const GridTetromino& shape) const
{
	for (const auto& loc : shape.getBlockLocsMappedToGrid()) {
		int x = loc.getX();
		int y = loc.getY();
	
		if (x < 0 || x >= Gameboard::MAX_X || y >= Gameboard::MAX_Y) {
			return false;
		}
	}
	return true;
}

void TetrisGame::determineSecondsPerTick()
{
	int level = score / 2000;

	secondsPerTick = MAX_SECONDS_PER_TICK - (level * 0.2);

	if (secondsPerTick < MIN_SECONDS_PER_TICK) {
		secondsPerTick = MIN_SECONDS_PER_TICK;
	}
}
