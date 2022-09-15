#pragma once

#include <map>
#include <sstream>

#include "GameState.h"
#include "Button.h"

class MenuState : public State
{
private:
	//Variables
	sf::Texture m_backgroundTexture;
	sf::RectangleShape m_background;
	sf::Font m_font;

	int m_MenuStateButtonWidth;
	int m_MenuStateButtonHeight;

	std::map<std::string, Button*> m_MenuStateButtons;

	//Initializer functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initButtons();
protected:
public:
	MenuState(sf::RenderWindow* window, std::stack<State*>* states);
	virtual ~MenuState();

	//Functions
	//Update
	void update();
	void updateMousePos();
	void updateButtons();

	//Render
	void render(sf::RenderWindow* window);
	void renderButtons(sf::RenderWindow* window);
};

