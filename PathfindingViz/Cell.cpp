#include "Cell.h"

Cell::Cell(int x, int y)
{
	this->x = x;
	this->y = y;

	this->cell.setPosition(this->x * GameState::gridSize + 1, this->y * GameState::gridSize + 1);
	this->cell.setSize(sf::Vector2f(20, 20));
	this->cell.setOutlineColor(sf::Color::Black);
	this->cell.setOutlineThickness(1.f);

	if (rand() % 100 < 37)
		this->wall = true;

	if (wall)
		this->cell.setFillColor(sf::Color::Black);
	else
		this->cell.setFillColor(sf::Color::White);
}

void Cell::passCell(Cell* grid[][40])
{
	for (int i = 0; i < GameState::mapSizeWidth; i++)
	{
		for (int j = 0; j < GameState::mapSizeHeight; j++)
		{
			this->grid[i][j] = grid[i][j];
		}
	}
}

void Cell::updateCell(sf::Color color)
{
	this->cell.setFillColor(color);
}

void Cell::addNeighbors(bool diagonals)
{
	int x = this->x;
	int y = this->y;
	if (x < GameState::mapSizeWidth - 1)
		this->neighbors.push_back(this->grid[x + 1][y]);
	if (x > 0)
		this->neighbors.push_back(this->grid[x - 1][y]);
	if (y < GameState::mapSizeHeight - 1)
		this->neighbors.push_back(this->grid[x][y + 1]);
	if (y > 0)
		this->neighbors.push_back(this->grid[x][y - 1]);
	if (diagonals)
	{
		if (x > 0 && y > 0)
			this->neighbors.push_back(this->grid[x - 1][y - 1]);

		if (x < GameState::mapSizeWidth - 1 && y > 0)
			this->neighbors.push_back(this->grid[x + 1][y - 1]);

		if (x > 0 && y < GameState::mapSizeHeight - 1)
			this->neighbors.push_back(this->grid[x - 1][y + 1]);

		if (x < GameState::mapSizeWidth - 1 && y < GameState::mapSizeHeight - 1)
			this->neighbors.push_back(this->grid[x + 1][y + 1]);
	}
}
