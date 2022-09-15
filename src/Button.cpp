#include "Button.h"

//-------------Constructors-Destructors------------
Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	m_buttonState = IDLE_BUTTON;

	m_shape.setPosition(sf::Vector2f(x, y));
	m_shape.setSize(sf::Vector2f(width, height));
	m_shape.setFillColor(sf::Color::Transparent);

	m_font = font;
	m_text.setFont(*m_font);
	m_text.setString(text);
	m_text.setFillColor(sf::Color::White);
	m_text.setCharacterSize(50.f);
	m_text.setPosition(
		m_shape.getPosition().x + (m_shape.getGlobalBounds().width / 2.f) - (m_text.getGlobalBounds().width / 2.f),
		m_shape.getPosition().y + (m_shape.getGlobalBounds().height / 2.f) - (m_text.getGlobalBounds().height / 2.f)
	);

	m_idleColor = idleColor;
	m_hoverColor = hoverColor;
	m_activeColor = activeColor;
}

Button::~Button()
{
	
}

//------------------Functions----------------------
bool Button::isPressed()
{
	if (m_buttonState == ACTIVE_BUTTON)
	{
		return true;
	}
	return false;
}

//------------------Update-------------------------
void Button::update(const sf::Vector2f mousePos, sf::RenderWindow* window)
{
	//Idle Color
	m_buttonState = IDLE_BUTTON;
	m_text.setOutlineColor(m_idleColor);
	m_text.setOutlineThickness(0);

	if (m_shape.getGlobalBounds().contains(mousePos))
	{
		//Hover Color
		m_buttonState = HOVER_BUTTON;
		m_text.setOutlineColor(m_hoverColor);
		m_text.setOutlineThickness(1.5f);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			m_buttonState = ACTIVE_BUTTON;
	}

	switch (m_buttonState)
	{
	case IDLE_BUTTON:
		m_text.setFillColor(m_idleColor);
		break;
	case HOVER_BUTTON:
		m_text.setFillColor(m_hoverColor);
		break;
	case ACTIVE_BUTTON:
		m_text.setFillColor(m_activeColor);
		break;
	default:
		m_text.setFillColor(sf::Color::Red);
		break;
	}
}

//------------------Render-------------------------
void Button::render(sf::RenderWindow* window)
{
	window->draw(m_shape);
	window->draw(m_text);
}
