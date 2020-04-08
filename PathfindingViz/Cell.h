#pragma once

#include <vector>
#include "SFML/Graphics.hpp"
#include "GameState.h"

extern 

class Cell
{
public:
	//Variables
	friend class GameState;
	
	bool wall = false;
	int x;
	int y;
	double f = 0.0;
	double g = 0.0;
	double h = 0.0;

	Cell* previous;
	Cell* grid[96][40];

	std::vector<Cell*> neighbors;
	sf::RectangleShape cell;

	//Constructor
	Cell(int x, int y);

	//Functions
	void passCell(Cell* grid[][40]);
	void updateCell(sf::Color color = sf::Color::White);
	void addNeighbors(bool);
};

