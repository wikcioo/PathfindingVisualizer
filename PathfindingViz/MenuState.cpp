#include "MenuState.h"

//--------------Initializer functions--------------
void MenuState::initVariables()
{
	this->MenuStateButtonWidth = 160;
	this->MenuStateButtonHeight = 70;
}

void MenuState::initBackground()
{
	this->background.setSize(sf::Vector2f
	(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y))
	);

	if (!this->backgroundTexture.loadFromFile("Images/menu4.jpg"))
	{
		throw "ERROR::MENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}
	this->background.setTexture(&this->backgroundTexture);
}

void MenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Consolas.ttf"))
	{
		throw "ERROR::MENUSTATE::FAILED_TO_LOAD_FONTS";
	}
}

void MenuState::initButtons()
{
	int buttonX = (this->window->getSize().x / 2) - (this->MenuStateButtonWidth / 2);
	int buttonY = (this->window->getSize().y / 2) - (this->MenuStateButtonHeight / 2);

	this->MenuStateButtons["PLAY"] = new Button(buttonX, buttonY - 60, this->MenuStateButtonWidth, this->MenuStateButtonHeight, &this->font, "Play",
		sf::Color(255, 51, 0), sf::Color(255, 51, 0), sf::Color(255, 51, 0));

	this->MenuStateButtons["EXIT"] = new Button(buttonX, buttonY + 60, this->MenuStateButtonWidth, this->MenuStateButtonHeight, &this->font, "Exit",
		sf::Color(255, 51, 0), sf::Color(255, 51, 0), sf::Color(255, 51, 0));
}

//-------------Constructors-Destructors------------
MenuState::MenuState(sf::RenderWindow* window, std::stack<State*>* states)
	: State(window, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initButtons();
}

MenuState::~MenuState()
{
	auto it = this->MenuStateButtons.begin();
	for (it = this->MenuStateButtons.begin(); it != this->MenuStateButtons.end(); ++it)
	{
		delete it->second;
	}
}

//------------------Functions----------------------
//------------------Update-------------------------
void MenuState::update()
{
	this->updateMousePos();
	this->updateButtons();
}

void MenuState::updateMousePos()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void MenuState::updateButtons()
{
	for (auto& it : this->MenuStateButtons)
	{
		it.second->update(static_cast<sf::Vector2f>(mousePosWindow), this->window);
	}

	//Play
	if (this->MenuStateButtons["PLAY"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->states));
	}

	//Quit
	if (this->MenuStateButtons["EXIT"]->isPressed())
	{
		this->endState();
	}
}

//------------------Render-------------------------
void MenuState::render(sf::RenderWindow* window)
{
	window->draw(this->background);

	this->renderButtons(window);

	//-------for-testing--------
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosWindow.x, this->mousePosWindow.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosWindow.x << " " << mousePosWindow.y;
	mouseText.setString(ss.str());
	window->draw(mouseText);
}

void MenuState::renderButtons(sf::RenderWindow* window)
{
	for (auto& it : MenuStateButtons)
	{
		it.second->render(window);
	}
}