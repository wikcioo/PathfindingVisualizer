#include "GameState.h"

//--------------Initializer functions--------------
void GameState::initVariables()
{
	srand(time(NULL));
	this->GameStateButtonWidth = 150;
	this->GameStateButtonHeight = 50;
	this->gameOver = false;
	this->includeDiagonals = true;
}

void GameState::initBackground()
{
	this->background.setSize(sf::Vector2f
	(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y))
	);

	if (!this->backgroundTexture.loadFromFile("Images/cubeStructure.jpg"))
	{
		throw "ERROR::MENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}
	this->background.setTexture(&this->backgroundTexture);
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Consolas.ttf"))
	{
		throw "ERROR::MENUSTATE::FAILED_TO_LOAD_FONTS";
	}
}

void GameState::initButtons()
{
	this->GameStateButtons["MENU"] = new Button(1400, 900, this->GameStateButtonWidth + 150, this->GameStateButtonHeight, &this->font, "Back to menu",
		sf::Color(255, 51, 0), sf::Color(255, 51, 0), sf::Color(255, 51, 0));

	this->GameStateButtons["START"] = new Button(100, 900, this->GameStateButtonWidth, this->GameStateButtonHeight, &this->font, "Start",
		sf::Color(255, 51, 0), sf::Color(255, 51, 0), sf::Color(255, 51, 0));

	this->GameStateButtons["STOP"] = new Button(300, 900, this->GameStateButtonWidth, this->GameStateButtonHeight, &this->font, "Stop",
		sf::Color(255, 51, 0), sf::Color(255, 51, 0), sf::Color(255, 51, 0));

	this->GameStateButtons["REFRESH"] = new Button(500, 900, this->GameStateButtonWidth, this->GameStateButtonHeight, &this->font, "Refresh",
		sf::Color(255, 51, 0), sf::Color(255, 51, 0), sf::Color(255, 51, 0));
}

void GameState::initGrid()
{
	for (size_t x = 0; x < this->mapSizeWidth; x++)
	{
		for (size_t y = 0; y < this->mapSizeHeight; y++)
		{
			this->cells[x][y] = new Cell(x, y);
		}
	}

	for (size_t x = 0; x < this->mapSizeWidth; x++)
	{
		for (size_t y = 0; y < this->mapSizeHeight; y++)
		{
			this->cells[x][y]->passCell(this->cells);
		}
	}

	for (size_t x = 0; x < this->mapSizeWidth; x++)
	{
		for (size_t y = 0; y < this->mapSizeHeight; y++)
		{
			this->cells[x][y]->addNeighbors(this->includeDiagonals);
		}
	}

	
	this->startingPoint = cells[0][35];
	this->startingPoint->wall = false;
	this->openSet.push_back(this->startingPoint);

	this->endingPoint = cells[mapSizeWidth - 1][20];
	this->endingPoint->wall = false;

	//this->tileSelector.setSize(sf::Vector2f(this->gridSize, this->gridSize));
	//this->tileSelector.setFillColor(sf::Color::Transparent);
	//this->tileSelector.setOutlineThickness(1.f);
	//this->tileSelector.setOutlineColor(sf::Color::Cyan);
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
	auto it = this->GameStateButtons.begin();
	for (it = this->GameStateButtons.begin(); it != this->GameStateButtons.end(); ++it)
	{
		delete it->second;
	}
}

double GameState::distanceCalculate(double x1, double y1, double x2, double y2)
{
	double x = x1 - x2;
	double y = y1 - y2;
	double dist;

	dist = pow(x, 2) + pow(y, 2);
	dist = sqrt(dist);

	return dist;
}

double GameState::heuristic(Cell* a, Cell* b)
{
	double d = distanceCalculate(a->x, a->y, b->x, b->y);
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
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	if (this->mousePosGrid.x >= 0.f && this->mousePosGrid.x < this->mapSizeWidth - 1)
		this->mousePosGrid.x = this->mousePosWindow.x / this->gridSize;
	else
		this->mousePosGrid.x = this->mousePosWindow.x / this->gridSize;


	if (this->mousePosGrid.y >= 0.f && this->mousePosGrid.y < this->mapSizeHeight - 1)
		this->mousePosGrid.y = this->mousePosWindow.y / this->gridSize;
	else
		this->mousePosGrid.y = this->mousePosWindow.y / this->gridSize;
}

void GameState::updateGameElements()
{
	this->tileSelector.setPosition(this->mousePosGrid.x * this->gridSize, this->mousePosGrid.y * this->gridSize);
}

void GameState::updateButtons()
{
	for (auto& it : this->GameStateButtons)
	{
		it.second->update(static_cast<sf::Vector2f>(this->mousePosWindow), this->window);
	}

	// Back to menu
	if (this->GameStateButtons["MENU"]->isPressed())
	{
		this->endState();
	}
	else if (this->GameStateButtons["START"]->isPressed())
	{
		this->startGame = true;
	}
	else if (this->GameStateButtons["STOP"]->isPressed())
	{
		this->startGame = false;
	}
	else if (this->GameStateButtons["REFRESH"]->isPressed())
	{
		this->startGame = false;
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

	/*if (point.x + 1 == this->mousePosGrid.x && point.y == this->mousePosGrid.y)
	{
		this->cells[point.x][point.y].setFillColor(sf::Color::White);
		point.x++;
	}
	if (point.y + 1 == this->mousePosGrid.y && point.x == this->mousePosGrid.x)
	{
		this->tileMap[point.x][point.y].setFillColor(sf::Color::White);
		point.y++;
	}
	if (point.x - 1 == this->mousePosGrid.x && point.y == this->mousePosGrid.y)
	{
		this->tileMap[point.x][point.y].setFillColor(sf::Color::White);
		point.x--;
	}
	if (point.y - 1 == this->mousePosGrid.y && point.x == this->mousePosGrid.x)
	{
		this->tileMap[point.x][point.y].setFillColor(sf::Color::White);
		point.y--;
	}

	if (point == this->startingPoint)
		this->tileMap[startingPoint.x][startingPoint.y].setFillColor(sf::Color::Blue);
	if (point == this->endingPoint)
		this->tileMap[endingPoint.x][endingPoint.y].setFillColor(sf::Color::Red);*/
}

void GameState::updateGrid()
{
	
	if (this->startGame)
	{
		if (!openSet.empty() && !this->gameOver)
		{
			int winner = 0;
			for (int i = 0; i < openSet.size(); i++)
			{
				if (openSet[i]->f < openSet[winner]->f)
				{
					winner = i;
				}
			}
			Cell* current = openSet[winner];
			
			if (current == this->endingPoint)
			{
				//Restore the path
				this->path.clear();
				Cell* temp = current;
				path.push_back(temp);
				while (temp->previous)
				{
					path.push_back(temp->previous);
					temp = temp->previous;
				}
				
				this->gameOver = true;
				std::cout << "DONE!" << std::endl;
			}

			openSet.erase(std::remove(openSet.begin(), openSet.end(), current), openSet.end());
			closedSet.push_back(current);

			std::vector<Cell*> neighbors = current->neighbors;
			for (int i = 0; i < neighbors.size(); i++)
			{
				Cell* neighbor = neighbors.at(i);

				if (std::find(closedSet.begin(), closedSet.end(), neighbor) == closedSet.end() && !neighbor->wall)
				{
					double tempG = current->g + 1;

					bool newPath = false;
					if (std::find(openSet.begin(), openSet.end(), neighbor) != openSet.end())
					{
						if (tempG < neighbor->g)
						{
							neighbor->g = tempG;
							newPath = true;
						}
						
					}
					else
					{
						neighbor->g = tempG;
						newPath = true;
						openSet.push_back(neighbor);
					}
					if (newPath)
					{
						neighbor->h = heuristic(neighbor, this->endingPoint);
						neighbor->f = neighbor->g + neighbor->h;
						neighbor->previous = current;
					}
				}
			}
		}
		else
		{
			this->gameOver = true;
		}
		

	}
}

void GameState::checkForEvents()
{
	while (this->window->pollEvent(this->event))
	{
		if (event.type == sf::Event::Closed)
			this->window->close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->window->close();
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
	for (auto& it : this->GameStateButtons)
	{
		it.second->render(window);
	}
}

void GameState::renderGrid(sf::RenderWindow* window)
{
	for (int i = 0; i < openSet.size(); i++)
	{
		openSet[i]->updateCell(sf::Color::Green);
	}
	for (int i = 0; i < closedSet.size(); i++)
	{
		closedSet[i]->updateCell(sf::Color::Red);
	}
	for (int i = 0; i < path.size(); i++)
	{
		path[i]->updateCell(sf::Color(0, 204, 255));
	}
	
	for (int x = 0; x < mapSizeWidth; x++)
	{
		for (int y = 0; y < mapSizeHeight; y++)
		{
			window->draw(cells[x][y]->cell);
		}
	}

	if (this->mousePosGrid.x >= 0.f && this->mousePosGrid.x < this->mapSizeWidth && this->mousePosGrid.y >= 0.f && this->mousePosGrid.y < this->mapSizeHeight)
		window->draw(this->tileSelector);
}
