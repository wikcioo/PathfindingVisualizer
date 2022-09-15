#pragma once

#include <fstream>
#include <stack>

#include "MenuState.h"
#include "SFML/Graphics.hpp"

class Game
{
private:
	//Variables
	std::stack<State*> m_states;
	sf::RenderWindow* m_window;
	bool m_fullscreen;

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

