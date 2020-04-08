#pragma once

#include <iostream>
#include <vector>

#include "Cell.h"
#include "State.h"
#include "Button.h"

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

	sf::Texture backgroundTexture;
	sf::Image image;
	sf::RectangleShape background;
	sf::Font font;

	int GameStateButtonWidth;
	int GameStateButtonHeight;
	bool isBg = false;
	bool startGame = false;
	bool includeDiagonals = false;

	std::map<std::string, Button*> GameStateButtons;

	//Grid variables
	Cell* startingPoint;
	Cell* endingPoint;

	bool gameOver;

	Cell* cells[mapSizeWidth][mapSizeHeight];

	std::vector<Cell*> openSet;
	std::vector<Cell*> closedSet;
	std::vector<Cell*> path;

	sf::RectangleShape shape;
	sf::RectangleShape tileSelector;
	sf::Event event;
	sf::Vector2u mousePosGrid;
	
	//Initializer functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initButtons();
	void initGrid();
protected:

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