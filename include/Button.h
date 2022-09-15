#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"

enum button_states{IDLE_BUTTON = 0, HOVER_BUTTON, ACTIVE_BUTTON};

class Button
{
private:
	//Variables
	sf::RectangleShape m_shape;
	sf::Font* m_font;
	sf::Text m_text;
	button_states m_buttonState;

	sf::Color m_idleColor;
	sf::Color m_hoverColor;
	sf::Color m_activeColor;
public:
	Button(float x, float y, float width, float height, sf::Font* font, std::string text,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	virtual ~Button();

	//Functions
	bool isPressed();

	//Update
	void update(const sf::Vector2f mousePos, sf::RenderWindow* window);

	//Render
	void render(sf::RenderWindow* window);
};

