#pragma once

#include <iostream>
#include <vector>
#include <cmath>

#include "State.h"
#include "Button.h"
#include "Cell.h"
#include "MazeGeneration.h"

class Cell;

class GameState : public State
{
public:
	//Constants
	constexpr static float gridSize{ 20 };
	constexpr static int mapSizeWidth{ 96 };
	constexpr static int mapSizeHeight{ 40 };
private:
	//Variables
	//Button variables
	friend class Cell;

	sf::Texture m_backgroundTexture;
	sf::Image m_image;
	sf::RectangleShape m_background;
	sf::Font m_font;

	int m_GameStateButtonWidth;
	int m_GameStateButtonHeight;
	bool m_isBg = false;
	bool m_startGame = false;
	bool m_includeDiagonals = false;

	std::map<std::string, Button*> m_GameStateButtons;

	//Grid variables
	Cell* m_startingPoint;
	Cell* m_endingPoint;

	bool m_gameOver;

	Cell* m_cells[mapSizeWidth][mapSizeHeight];

	std::vector<Cell*> m_openSet;
	std::vector<Cell*> m_closedSet;
	std::vector<Cell*> m_path;

	sf::RectangleShape m_shape;
	sf::RectangleShape m_tileSelector;
	sf::Event m_event;
	sf::Vector2u m_mousePosGrid;
	
	//Initializer functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initButtons();
	void initGrid();

public:
	//Constructors Destructors
	GameState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~GameState();

	//Functions
	double distanceCalculate(double, double, double, double);
	double heuristic(Cell* a, Cell* b);
	bool diagonals(bool &d);
	//Update
	void update();
	void updateMousePosGrid();
	void updateGameElements();
	void updateButtons();
	void updateStartingAndEndingPoints(sf::Vector2i& point);
	void updateGrid();
	void checkForEvents();

	//Render
	void render(sf::RenderWindow* window);
	void renderButtons(sf::RenderWindow* window);
	void renderGrid(sf::RenderWindow* window);
};
