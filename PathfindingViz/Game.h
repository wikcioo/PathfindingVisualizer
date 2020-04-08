#pragma once

#include <fstream>
#include <stack>

#include "MenuState.h"
#include "SFML/Graphics.hpp"

class Game
{
private:
	//Variables
	std::stack<State*> states;
	sf::RenderWindow* window;
	bool fullscreen;

	//Initializer functions
	void initWindow();
	void initStates();
public:
	//Constructors Destructors
	Game();
	virtual ~Game();

	//Functions
	//Update
	void update();

	//Render
	void render();

	//Core
	void run();
};

