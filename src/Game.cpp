#include "Game.h"
#include <errno.h>
#include <string.h>

//--------------Initializer functions--------------
void Game::initWindow()
{
	std::ifstream ifs("config/window_settings.ini");
    if (!ifs.is_open())
    {
        std::cerr << "Failed to open window configuration settings!" << std::endl;
        std::cout << "Error: " << strerror(errno) << std::endl;
        std::exit(1);
    }

	std::string title{};
	sf::VideoMode video_mode{};
	bool full_screen{};
	unsigned int frame_rate_limit{};
	bool vertical_sync_enabled{};

    std::getline(ifs, title);
    ifs >> video_mode.width >> video_mode.height;
    ifs >> full_screen;
    ifs >> frame_rate_limit;
    ifs >> vertical_sync_enabled;

	m_fullscreen = full_screen;
	if (m_fullscreen)
		m_window = new sf::RenderWindow(video_mode, title, sf::Style::Fullscreen);
	else
		m_window = new sf::RenderWindow(video_mode, title, sf::Style::Close | sf::Style::Titlebar);

	m_window->setFramerateLimit(frame_rate_limit);
	m_window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates()
{
	m_states.push(new MenuState(m_window, &m_states));
}

//-------------Constructors-Destructors------------
Game::Game()
{
	this->initWindow();
	this->initStates();
}

Game::~Game()
{
	delete m_window;

	while (!m_states.empty())
	{
		delete m_states.top();
		m_states.pop();
	}
}

//------------------Functions----------------------
//------------------Update-------------------------
void Game::update()
{
	if (!m_states.empty())
	{
		m_states.top()->update();

		if (m_states.top()->getQuit())
		{
			m_states.top()->endState();
			delete m_states.top();
			m_states.pop();
		}
	}
	else
	{
		//this->endApplication();
		m_window->close();
	}
}

//------------------Render-------------------------
void Game::render()
{
	m_window->clear();

	//Draw objects
	if (!m_states.empty())
		m_states.top()->render(m_window);

	m_window->display();
}

//------------------Core---------------------------
void Game::run()
{
	while (m_window->isOpen())
	{
		this->update();
		this->render();
	}
}
