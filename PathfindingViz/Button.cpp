#include "Button.h"

//-------------Constructors-Destructors------------
Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = IDLE_BUTTON;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(sf::Color::Transparent);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(50.f);
	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - (this->text.getGlobalBounds().width / 2.f),
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - (this->text.getGlobalBounds().height / 2.f)
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
}

Button::~Button()
{
	
}

//------------------Functions----------------------
bool Button::isPressed()
{
	if (this->buttonState == ACTIVE_BUTTON)
	{
		return true;
	}
	return false;
}

//------------------Update-------------------------
void Button::update(const sf::Vector2f mousePos, sf::RenderWindow* window)
{
	//Idle Color
	this->buttonState = IDLE_BUTTON;
	this->text.setOutlineColor(this->idleColor);
	this->text.setOutlineThickness(0);

	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		//Hover Color
		this->buttonState = HOVER_BUTTON;
		this->text.setOutlineColor(this->hoverColor);
		this->text.setOutlineThickness(1.5f);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			this->buttonState = ACTIVE_BUTTON;
	}

	switch (this->buttonState)
	{
	case IDLE_BUTTON:
		this->text.setFillColor(this->idleColor);
		break;
	case HOVER_BUTTON:
		this->text.setFillColor(this->hoverColor);
		break;
	case ACTIVE_BUTTON:
		this->text.setFillColor(this->activeColor);
		break;
	default:
		this->text.setFillColor(sf::Color::Red);
		break;
	}
}

//------------------Render-------------------------
void Button::render(sf::RenderWindow* window)
{
	window->draw(shape);
	window->draw(text);
}
