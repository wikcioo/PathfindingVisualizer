#include "Cell.h"

Cell::Cell(int x, int y)
{
	m_x = x;
	m_y = y;

	m_cell.setPosition(m_x * GameState::gridSize + 1, m_y * GameState::gridSize + 1);
	m_cell.setSize(sf::Vector2f(20, 20));
	m_cell.setOutlineColor(sf::Color::Black);
	m_cell.setOutlineThickness(1.f);

    /*
	if (rand() % 100 < 50)
m:_wall = true;
    */

    /*
	if (m_wall)
		m_cell.setFillColor(sf::Color::Black);
	else
		m_cell.setFillColor(sf::Color::White);
    */
}

void Cell::passCell(Cell* grid[][40])
{
	for (int i = 0; i < GameState::mapSizeWidth; i++)
	{
		for (int j = 0; j < GameState::mapSizeHeight; j++)
		{
			m_grid[i][j] = grid[i][j];
		}
	}
}

void Cell::updateCell(sf::Color color)
{
	m_cell.setFillColor(color);
}

void Cell::addNeighbors(bool diagonals)
{
	int x = m_x;
	int y = m_y;
	if (x < GameState::mapSizeWidth - 1)
		m_neighbors.push_back(m_grid[x + 1][y]);
	if (x > 0)
		m_neighbors.push_back(m_grid[x - 1][y]);
	if (y < GameState::mapSizeHeight - 1)
		m_neighbors.push_back(m_grid[x][y + 1]);
	if (y > 0)
		m_neighbors.push_back(m_grid[x][y - 1]);
	if (diagonals)
	{
		if (x > 0 && y > 0)
			m_neighbors.push_back(m_grid[x - 1][y - 1]);

		if (x < GameState::mapSizeWidth - 1 && y > 0)
			m_neighbors.push_back(m_grid[x + 1][y - 1]);

		if (x > 0 && y < GameState::mapSizeHeight - 1)
			m_neighbors.push_back(m_grid[x - 1][y + 1]);

		if (x < GameState::mapSizeWidth - 1 && y < GameState::mapSizeHeight - 1)
			m_neighbors.push_back(m_grid[x + 1][y + 1]);
	}
}

void Cell::setWall()
{
    m_grid[m_x][m_y]->m_wall = true;
}
