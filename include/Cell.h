#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include "GameState.h"

//class GameState;

class Cell
{
public:
	//Variables
	// friend class GameState;
	
	bool m_wall = false;
	int m_x;
	int m_y;
	double m_f = 0.0;
	double m_g = 0.0;
	double m_h = 0.0;

	Cell* m_previous;
	Cell* m_grid[96][40];

	std::vector<Cell*> m_neighbors;
	sf::RectangleShape m_cell;

	//Constructor
	Cell(int x, int y);

	//Functions
	void passCell(Cell* grid[][40]);
	void updateCell(sf::Color color = sf::Color::White);
	void addNeighbors(bool);
    void setWall();
};

