#include "Game.h"

//--------------Initializer functions--------------
void Game::initWindow()
{
	std::ifstream ifs("Config/window_settings.ini");

	std::string title{};
	sf::VideoMode video_mode{};
	bool fullscreen{};
	unsigned int frame_rate_limit{};
	bool vertical_sync_enabled{};

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> video_mode.width >> video_mode.height;
		ifs >> fullscreen;
		ifs >> frame_rate_limit;
		ifs >> vertical_sync_enabled;
	}

	this->fullscreen = fullscreen;
	if (this->fullscreen)
		this->window = new sf::RenderWindow(video_mode, title, sf::Style::Fullscreen);
	else
		this->window = new sf::RenderWindow(video_mode, title, sf::Style::Close | sf::Style::Titlebar);

	this->window->setFramerateLimit(frame_rate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates()
{
	this->states.push(new MenuState(this->window, &this->states));
}

//-------------Constructors-Destructors------------
Game::Game()
{
	this->initWindow();
	this->initStates();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}

//------------------Functions----------------------
//------------------Update-------------------------
void Game::update()
{
	if (!this->states.empty())
	{
		this->states.top()->update();

		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	else
	{
		//this->endApplication();
		this->window->close();
	}
}

//------------------Render-------------------------
void Game::render()
{
	this->window->clear();

	//Draw objects
	if (!this->states.empty())
		this->states.top()->render(this->window);

	this->window->display();
}

//------------------Core---------------------------
void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}