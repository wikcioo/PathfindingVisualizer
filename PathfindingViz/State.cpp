#include "State.h"

//-------------Constructors-Destructors------------
State::State(sf::RenderWindow* window, std::stack<State*>* states)
{
	this->window = window;
	this->states = states;
	this->quit = false;
}

State::~State()
{

}

//------------------Functions----------------------
const bool& State::getQuit() const
{
	if (this->quit)
		return true;
	return false;
}

void State::endState()
{
	this->quit = true;
}
