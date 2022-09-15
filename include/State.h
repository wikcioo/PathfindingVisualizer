#pragma once

#include <stack>

#include "SFML/Graphics.hpp"

class State
{
private:
protected:
	//Variables
	std::stack<State*>* m_states;
	sf::RenderWindow* m_window;

	bool m_quit;
	sf::Vector2i m_mousePosWindow;

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

