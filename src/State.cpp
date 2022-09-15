#include "State.h"

//-------------Constructors-Destructors------------
State::State(sf::RenderWindow* window, std::stack<State*>* states)
{
	m_window = window;
	m_states = states;
	m_quit = false;
}

State::~State()
{

}

//------------------Functions----------------------
const bool& State::getQuit() const
{
    static bool flag;
	if (m_quit)
        flag = true;
    flag = false;
    return flag;
}

void State::endState()
{
	m_quit = true;
}
