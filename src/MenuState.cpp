#include "MenuState.h"

//--------------Initializer functions--------------
void MenuState::initVariables()
{
	m_MenuStateButtonWidth = 160;
	m_MenuStateButtonHeight = 70;
}

void MenuState::initBackground()
{
	m_background.setSize(sf::Vector2f
	(
		static_cast<float>(m_window->getSize().x),
		static_cast<float>(m_window->getSize().y))
	);

	if (!m_backgroundTexture.loadFromFile("res/images/menu4.jpg"))
	{
		throw "ERROR::MENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}
	m_background.setTexture(&m_backgroundTexture);
}

void MenuState::initFonts()
{
	if (!m_font.loadFromFile("res/fonts/Consolas.ttf"))
	{
		throw "ERROR::MENUSTATE::FAILED_TO_LOAD_FONTS";
	}
}

void MenuState::initButtons()
{
	int buttonX = (m_window->getSize().x / 2) - (m_MenuStateButtonWidth / 2);
	int buttonY = (m_window->getSize().y / 2) - (m_MenuStateButtonHeight / 2);

	m_MenuStateButtons["PLAY"] = new Button(buttonX, buttonY - 60, m_MenuStateButtonWidth, m_MenuStateButtonHeight, &m_font, "Play",
		sf::Color(255, 51, 0), sf::Color(255, 51, 0), sf::Color(255, 51, 0));

	m_MenuStateButtons["EXIT"] = new Button(buttonX, buttonY + 60, m_MenuStateButtonWidth, m_MenuStateButtonHeight, &m_font, "Exit",
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
	auto it = m_MenuStateButtons.begin();
	for (it = m_MenuStateButtons.begin(); it != m_MenuStateButtons.end(); ++it)
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
	m_mousePosWindow = sf::Mouse::getPosition(*m_window);
}

void MenuState::updateButtons()
{
	for (auto& it : m_MenuStateButtons)
	{
		it.second->update(static_cast<sf::Vector2f>(m_mousePosWindow), m_window);
	}

	//Play
	if (m_MenuStateButtons["PLAY"]->isPressed())
	{
		m_states->push(new GameState(m_window, m_states));
	}

	//Quit
	if (m_MenuStateButtons["EXIT"]->isPressed())
	{
		this->endState();
	}
}

//------------------Render-------------------------
void MenuState::render(sf::RenderWindow* window)
{
	window->draw(m_background);

	this->renderButtons(window);

	//-------for-testing--------
	sf::Text mouseText;
	mouseText.setPosition(m_mousePosWindow.x, m_mousePosWindow.y - 50);
	mouseText.setFont(m_font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << m_mousePosWindow.x << " " << m_mousePosWindow.y;
	mouseText.setString(ss.str());
	window->draw(mouseText);
}

void MenuState::renderButtons(sf::RenderWindow* window)
{
	for (auto& it : m_MenuStateButtons)
	{
		it.second->render(window);
	}
}
