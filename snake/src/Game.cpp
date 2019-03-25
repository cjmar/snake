#include "Game.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

std::pair<int, int> UP = { 0, -1 };
std::pair<int, int> DOWN = { 0, 1 };
std::pair<int, int> LEFT = { -1, 0 };
std::pair<int, int> RIGHT = { 1, 0 };

Game::Game() 
{

};

Game::~Game()
{
	appPtr = nullptr;
	delete appPtr;

	snake = nullptr;
	delete snake;

	food = nullptr;
	delete food;

}

void Game::init(int w, int h, ASCIIui* ptr)
{
	appPtr = ptr;
	width = w; //64
	height = h;//40

	tickRate = 1; //How many frames pass before the game updates
	tick = tickRate;	  //Container for frames passed to measure time

	snake = new Snake(width / 5, height / 2, RIGHT);
	food = new Food(1, 4, width - 1, height - 1);
	food->setPointValue(1);
	snake->setBoardDim(1, 4, width - 1, height - 1);
	gameState = GameStartInfo;

	//Build vector map
	for (int x = 0; x < width; x++)
	{
		std::vector<char> col;
		for (int y = 0; y < height; y++)
		{
			//Leave room at top for text
			if (x == 0 || y == 3 || x == width - 1|| y == height - 1)
			{
				col.push_back('#');
			}
			else col.push_back(' ');			
		}
		map.push_back(col);
	}

	//Draw the initial map
	drawMap();
	//setMessageMiddle("This is a message in the middle of the screen", height / 2);
	//setMessageMiddle("A new line", height / 2 + 1);
}

void Game::update()
{
	std::stringstream s1;
	s1 << " Score: " << food->getScore();
	setMessageTop(s1.str(), 2, false);

	//Check for if the snake is a live or not

	switch (gameState)
	{
	case GameStartInfo:
		setMessageMiddle("Welcome to ASCII Snake", height / 2);
		setMessageMiddle("Source can be found at:", height / 2 + 1);
		setMessageMiddle("github.com/cjmar/snake", height / 2 + 2);
		setMessageMiddle("Press Space to start", height / 2 + 4);
		toggle = true;
		break;

		//Main game loop
	case GameOngoing:
	{
		//Generate food if it doesnt exist on the map
		if (!food->foodOnMap())
		{
			food->genFood(snake->getBody());
		}
		//Check to see if the snake hit the food
		int xpos = snake->getBody().at(0).first;
		int ypos = snake->getBody().at(0).second;
		if (xpos == food->getFoodLoc().first && ypos == food->getFoodLoc().second)
		{
			snake->hitFood();
			//If theres no room left on the map for the snake to grow, then the game has been won
			if (food->genFood(snake->getBody()))
			{
				gameState = GameWon;
			}
		}
		//Draw the food on the map
		appPtr->setLetter(food->getFoodLoc().first, food->getFoodLoc().second, '@');

		//Draw the snake
		{
			int index = 0;
			for (std::pair<int, int> part : snake->getBody())
			{
				if (index == 0) appPtr->setLetter(part.first, part.second, 'X');
				else appPtr->setLetter(part.first, part.second, 'o');
				index++;
			}
		}
		//Move the snake
		if (tick > tickRate)
		{
			int xpos = snake->getBody().at(0).first;
			int ypos = snake->getBody().at(1).second;

			if (snake->isAlive())
			{
				snake->move();
			}
			else gameState = GameLost;

			tick = 0;
		}
		else
		{
			tick++;
		}
		break;
	}

	case GameWon:
		if (toggle)
		{
			recordScore(true);
			toggle = false;
		}
		showScoreScreen("You Won");
		break;

	case GameLost:
		if (toggle)
		{
			recordScore(false);
			toggle = false;
		}
		showScoreScreen("You Lost");
		break;
	}
}

void Game::eventHandle()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			appPtr->quit();
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_w:
				snake->setDirection(UP);
				break;

			case SDLK_a:
				snake->setDirection(LEFT);
				break;

			case SDLK_s:
				snake->setDirection(DOWN);
				break;

			case SDLK_d:
				snake->setDirection(RIGHT);
				break;

			case SDLK_SPACE:
				if (gameState == GameWon || gameState == GameLost || gameState == GameStartInfo)
				{
					gameState = GameOngoing;
					toggle = true;
					drawMap();
					snake->reset();
					food->resetScore();
					food->genFood(snake->getBody());
				}
				break;

			/*
			case SDLK_z: //Cheat key
				gameState = GameWon;
				break;
			*/

			case SDLK_ESCAPE:
				gameState = GameStartInfo;
				drawMap();
				snake->reset();
				food->resetScore();
				food->genFood(snake->getBody());
				break;
			}
		}
	}
}

void Game::setMessageTop(std::string msg, int yVal, bool leftAlign = true)
{
	int msgLength = 0;
	if (msg.length() > width - 2) msgLength = width - 3;
	else msgLength = msg.length();

	if (leftAlign)
	{
		int x = 2;
		for (unsigned int i = 0; i < msgLength; i++)
		{
			appPtr->setLetter(x, yVal, msg[i]);
			x++;
		}
	}
	else if(!leftAlign)
	{
		int x = width-2;
		for (int i = msgLength; i >= 0; i--)
		{
			appPtr->setLetter(x, yVal, msg[i]);
			x--;
		}
	}
}

void Game::setMessageMiddle(std::string msg, int yVal)
{
	unsigned int x = (width / 2) - (msg.length() / 2);

	for (unsigned int i = 0; i < msg.length(); i++)
	{
		appPtr->setLetter(x, yVal, msg[i]);
		x++;
	}
}

/*
	Just draws the map
*/
void Game::drawMap()
{
	//Draw the initialized map
	for (int y = 0; y < height; y++)
		for (int x = 0; x < width; x++)
			appPtr->setLetter(x, y, map[x][y]);

	setMessageTop("github.com/cjmar/snake", 0, true);
	setMessageTop("Esc to reset", 2, true);
}

void Game::showScoreScreen(std::string msg)
{
	int h = 6;
	setMessageMiddle(msg, h);
	std::stringstream s1;
	s1 << "Final score: " << food->getScore();
	setMessageMiddle(s1.str(), h + 1);

	std::stringstream s2;
	s2 << "Games Won:" << scores[0];
	setMessageMiddle(s2.str(), h + 3);

	for (int i = 1; i < 4; i++)
	{
		std::stringstream ss;
		ss << i << " : " << scores[i];
		setMessageMiddle(ss.str(), h + 3 + i);
	}

	setMessageMiddle("Press Space to play again", h + 8);

	
}

void Game::recordScore(bool won_game)
{
	loadBinaryFile();

	int gamesWon = scores[0];

	if (won_game)
	{
		gamesWon++;
	}

	scores[0] = food->getScore();

	std::sort(std::begin(scores), std::end(scores));
	std::reverse(std::begin(scores), std::end(scores));

	scores[3] = scores[2];
	scores[2] = scores[1];
	scores[1] = scores[0];
	scores[0] = gamesWon;

	std::ofstream fout;
	fout.open("data/previous.scores", std::ios::binary);
	if (fout.is_open())
	{
		for (int i = 0; i < 4; i++)
		{
			int aNumber = scores[i];
			fout.write((char*) &aNumber, sizeof(int));
		}
	}
	else
	{
		std::cout << "Can't open File\n";
	}
	fout.close();
}

void Game::loadBinaryFile()
{
	//Get previous scores
	std::ifstream fin;
	fin.open("data/previous.scores", std::ios::binary);
	if (fin.is_open())
	{
		for (int i = 0; i < 4; i++)
		{
			int aNumber;
			fin.read((char*)&aNumber, sizeof(int));
			scores[i] = aNumber;
		}
	}
	fin.close();

}