#include "GameState.h"

//--------------Initializer functions--------------
void GameState::initVariables()
{
	srand(time(NULL));
	m_GameStateButtonWidth = 150;
	m_GameStateButtonHeight = 50;
	m_gameOver = false;
	m_includeDiagonals = true;
}

void GameState::initBackground()
{
	m_background.setSize(sf::Vector2f
	(
		static_cast<float>(m_window->getSize().x),
		static_cast<float>(m_window->getSize().y))
	);

	if (!m_backgroundTexture.loadFromFile("res/images/cubeStructure.jpg"))
	{
		throw "ERROR::MENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}
	m_background.setTexture(&m_backgroundTexture);
}

void GameState::initFonts()
{
	if (!m_font.loadFromFile("res/fonts/Consolas.ttf"))
	{
		throw "ERROR::MENUSTATE::FAILED_TO_LOAD_FONTS";
	}
}

void GameState::initButtons()
{
	m_GameStateButtons["MENU"] = new Button(1400, 900, m_GameStateButtonWidth + 150, m_GameStateButtonHeight, &m_font, "Back to menu",
		sf::Color(255, 51, 0), sf::Color(255, 51, 0), sf::Color(255, 51, 0));

	m_GameStateButtons["START"] = new Button(100, 900, m_GameStateButtonWidth, m_GameStateButtonHeight, &m_font, "Start",
		sf::Color(255, 51, 0), sf::Color(255, 51, 0), sf::Color(255, 51, 0));

	m_GameStateButtons["STOP"] = new Button(300, 900, m_GameStateButtonWidth, m_GameStateButtonHeight, &m_font, "Stop",
		sf::Color(255, 51, 0), sf::Color(255, 51, 0), sf::Color(255, 51, 0));

	m_GameStateButtons["REFRESH"] = new Button(500, 900, m_GameStateButtonWidth, m_GameStateButtonHeight, &m_font, "Refresh",
		sf::Color(255, 51, 0), sf::Color(255, 51, 0), sf::Color(255, 51, 0));
}

void GameState::initGrid()
{
    char maze[HEIGHT][WIDTH];

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			maze[i][j] = WALL_CHAR;
		}
	}

    createMaze(maze);

	for (size_t y = 0; y < this->mapSizeHeight; y++)
	{
		for (size_t x = 0; x < this->mapSizeWidth; x++)
		{
			m_cells[x][y] = new Cell(x, y);
            if (maze[x][y] == WALL_CHAR)
            {
                m_cells[x][y]->m_wall = true;
                m_cells[x][y]->m_cell.setFillColor(sf::Color::Black);
            }
            else
            {
                m_cells[x][y]->m_cell.setFillColor(sf::Color::White);
            }
		}
	}

	for (size_t x = 0; x < this->mapSizeWidth; x++)
	{
		for (size_t y = 0; y < this->mapSizeHeight; y++)
		{
			m_cells[x][y]->passCell(m_cells);
		}
	}

	for (size_t x = 0; x < this->mapSizeWidth; x++)
	{
		for (size_t y = 0; y < this->mapSizeHeight; y++)
		{
			m_cells[x][y]->addNeighbors(m_includeDiagonals);
		}
	}

	
	m_startingPoint = m_cells[3][35];
	m_startingPoint->m_wall = false;
	m_openSet.push_back(m_startingPoint);

	m_endingPoint = m_cells[mapSizeWidth - 1][20];
	m_endingPoint->m_wall = false;

	//m_tileSelector.setSize(sf::Vector2f(this->gridSize, this->gridSize));
	//m_tileSelector.setFillColor(sf::Color::Transparent);
	//m_tileSelector.setOutlineThickness(1.f);
	//m_tileSelector.setOutlineColor(sf::Color::Cyan);
}

//-------------Constructors-Destructors------------
GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states)
	: State(window, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initButtons();
	this->initGrid();
}

GameState::~GameState()
{
	auto it = m_GameStateButtons.begin();
	for (it = m_GameStateButtons.begin(); it != m_GameStateButtons.end(); ++it)
	{
		delete it->second;
	}
}

double GameState::distanceCalculate(double x1, double y1, double x2, double y2)
{
	double x = x1 - x2;
	double y = y1 - y2;
	double dist;

	dist = std::pow(x, 2) + std::pow(y, 2);
	dist = std::sqrt(dist);

	return dist;
}

double GameState::heuristic(Cell* a, Cell* b)
{
	double d = distanceCalculate(a->m_x, a->m_y, b->m_x, b->m_y);
	//double d = std::abs(a->x - b->x) + std::abs(b->x - b->y);
	return d;
}

bool GameState::diagonals(bool &d)
{
	if (d) return true;
	return false;
}

//------------------Functions----------------------


//------------------Update-------------------------
void GameState::update()
{
	this->updateMousePosGrid();
	//this->updateGameElements();
	this->updateButtons();
	this->updateGrid();
	this->checkForEvents();
}

void GameState::updateMousePosGrid()
{
	m_mousePosWindow = sf::Mouse::getPosition(*m_window);

	if (m_mousePosGrid.x >= 0.f && m_mousePosGrid.x < this->mapSizeWidth - 1)
		m_mousePosGrid.x = m_mousePosWindow.x / this->gridSize;
	else
		m_mousePosGrid.x = m_mousePosWindow.x / this->gridSize;


	if (m_mousePosGrid.y >= 0.f && m_mousePosGrid.y < this->mapSizeHeight - 1)
		m_mousePosGrid.y = m_mousePosWindow.y / this->gridSize;
	else
		m_mousePosGrid.y = m_mousePosWindow.y / this->gridSize;
}

void GameState::updateGameElements()
{
	m_tileSelector.setPosition(m_mousePosGrid.x * this->gridSize, m_mousePosGrid.y * this->gridSize);
}

void GameState::updateButtons()
{
	for (auto& it : m_GameStateButtons)
	{
		it.second->update(static_cast<sf::Vector2f>(m_mousePosWindow), m_window);
	}

	// Back to menu
	if (m_GameStateButtons["MENU"]->isPressed())
	{
		this->endState();
	}
	else if (m_GameStateButtons["START"]->isPressed())
	{
		m_startGame = true;
	}
	else if (m_GameStateButtons["STOP"]->isPressed())
	{
		m_startGame = false;
	}
	else if (m_GameStateButtons["REFRESH"]->isPressed())
	{
		m_startGame = false;
		for (size_t x = 0; x < this->mapSizeWidth; x++)
		{
			for (size_t y = 0; y < this->mapSizeHeight; y++)
			{
				
			}
		}
	}
}

void GameState::updateStartingAndEndingPoints(sf::Vector2i& point)
{
	this->updateMousePosGrid();

	/*if (point.x + 1 == m_mousePosGrid.x && point.y == m_mousePosGrid.y)
	{
		m_cells[point.x][point.y].setFillColor(sf::Color::White);
		point.x++;
	}
	if (point.y + 1 == m_mousePosGrid.y && point.x == m_mousePosGrid.x)
	{
		this->tileMap[point.x][point.y].setFillColor(sf::Color::White);
		point.y++;
	}
	if (point.x - 1 == m_mousePosGrid.x && point.y == m_mousePosGrid.y)
	{
		this->tileMap[point.x][point.y].setFillColor(sf::Color::White);
		point.x--;
	}
	if (point.y - 1 == m_mousePosGrid.y && point.x == m_mousePosGrid.x)
	{
		this->tileMap[point.x][point.y].setFillColor(sf::Color::White);
		point.y--;
	}

	if (point == m_startingPoint)
		this->tileMap[startingPoint.x][startingPoint.y].setFillColor(sf::Color::Blue);
	if (point == m_endingPoint)
		this->tileMap[endingPoint.x][endingPoint.y].setFillColor(sf::Color::Red);*/
}

void GameState::updateGrid()
{
	
	if (m_startGame)
	{
		if (!m_openSet.empty() && !m_gameOver)
		{
			int winner = 0;
			for (std::size_t i = 0; i < m_openSet.size(); i++)
			{
				if (m_openSet[i]->m_f < m_openSet[winner]->m_f)
				{
					winner = i;
				}
			}
			Cell* current = m_openSet[winner];
			
			if (current == m_endingPoint)
			{
				//Restore the path
				this->m_path.clear();
				Cell* temp = current;
				m_path.push_back(temp);
				while (temp->m_previous)
				{
					m_path.push_back(temp->m_previous);
					temp = temp->m_previous;
				}
				
				m_gameOver = true;
				std::cout << "DONE!" << std::endl;
			}

			m_openSet.erase(std::remove(m_openSet.begin(), m_openSet.end(), current), m_openSet.end());
			m_closedSet.push_back(current);

			std::vector<Cell*> neighbors = current->m_neighbors;
			for (std::size_t i = 0; i < neighbors.size(); i++)
			{
				Cell* neighbor = neighbors.at(i);

				if (std::find(m_closedSet.begin(), m_closedSet.end(), neighbor) == m_closedSet.end() && !neighbor->m_wall)
				{
					double tempG = current->m_g + 1;

					bool newPath = false;
					if (std::find(m_openSet.begin(), m_openSet.end(), neighbor) != m_openSet.end())
					{
						if (tempG < neighbor->m_g)
						{
							neighbor->m_g = tempG;
							newPath = true;
						}
						
					}
					else
					{
						neighbor->m_g = tempG;
						newPath = true;
						m_openSet.push_back(neighbor);
					}
					if (newPath)
					{
						neighbor->m_h = heuristic(neighbor, m_endingPoint);
						neighbor->m_f = neighbor->m_g + neighbor->m_h;
						neighbor->m_previous = current;
					}
				}
			}
		}
		else
		{
			m_gameOver = true;
		}
		

	}
}

void GameState::checkForEvents()
{
	while (m_window->pollEvent(m_event))
	{
		if (m_event.type == sf::Event::Closed)
			m_window->close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			m_window->close();
	}
}

//------------------Render-------------------------
void GameState::render(sf::RenderWindow* window)
{
	this->renderGrid(window);
	this->renderButtons(window);
}

void GameState::renderButtons(sf::RenderWindow* window)
{
	for (auto& it : m_GameStateButtons)
	{
		it.second->render(window);
	}
}

void GameState::renderGrid(sf::RenderWindow* window)
{
	for (std::size_t i = 0; i < m_openSet.size(); i++)
	{
		m_openSet[i]->updateCell(sf::Color::Green);
	}
	for (std::size_t i = 0; i < m_closedSet.size(); i++)
	{
		m_closedSet[i]->updateCell(sf::Color::Red);
	}
	for (std::size_t i = 0; i < m_path.size(); i++)
	{
		m_path[i]->updateCell(sf::Color(0, 204, 255));
	}
	
	for (int x = 0; x < mapSizeWidth; x++)
	{
		for (int y = 0; y < mapSizeHeight; y++)
		{
			window->draw(m_cells[x][y]->m_cell);
		}
	}

	if (m_mousePosGrid.x >= 0.f && m_mousePosGrid.x < this->mapSizeWidth && m_mousePosGrid.y >= 0.f && m_mousePosGrid.y < this->mapSizeHeight)
		window->draw(m_tileSelector);
}
