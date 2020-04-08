#pragma once

#include <stack>

#include "SFML/Graphics.hpp"

class State
{
private:
protected:
	//Variables
	std::stack<State*>* states;
	sf::RenderWindow* window;

	bool quit;
	sf::Vector2i mousePosWindow;

public:
	//Constructors Destructors
	State(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;
	void endState();

	//Update
	virtual void update() = 0;

	//Render
	virtual void render(sf::RenderWindow* window) = 0;
};

