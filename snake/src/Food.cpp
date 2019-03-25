#include "Food.h"
#include <time.h>
#include <stdlib.h>
#include <algorithm>

Food::Food() {}

Food::Food(int sX, int sY, int eX, int eY)
{
	boardStartX = sX;
	boardEndX = eX;
	boardStartY = sY;
	boardEndY = eY;

	srand(time(NULL));
	score = -1;
	foodLoc = std::make_pair(0, 0);
	pointValue = 0;
}

bool Food::genFood(std::vector<std::pair<int, int>> snakeBody)
{
	bool winner = false;
	//Initialize space on map
	std::vector<std::pair<int, int>> map;

	//food = new Food(1, 4, width - 1, height - 1);
	for(int x = boardStartX; x < boardEndX; x++)
		for (int y = boardStartY; y < boardEndY; y++)
		{
			std::pair<int, int> p = std::make_pair(x, y);
			map.push_back(p);
		}

	//Remove places where snake exists, starting with back
	for (int i = snakeBody.size() - 1; i > 0; i--)
	{
		//If we found something then it needs to be removed from free
		std::vector<std::pair<int, int>>::iterator it = std::find(map.begin(), map.end(), snakeBody[i]);
		if (it != map.end())
		{ 
			//free.erase(free.begin() + i);
			it = map.erase(it);
		}
	}
	//Random index from free to get a viable location
	if (map.size() != 0)
	{
		int R = rand() % map.size();
		foodLoc = map[R];
		incrementScore();
	}
	//If map size is 0, then the whole board is taken up by the snake
	else winner = true;

	return winner;
}

std::pair<int, int> Food::getFoodLoc()
{
	return foodLoc;
}

bool Food::foodOnMap()
{
	bool onMap = false;
	if (foodLoc.first != 0 && foodLoc.second != 0)
	{
		onMap = true;
	}
	return onMap;
}

int Food::getScore()
{
	return score;
}

void Food::incrementScore()
{
	score += pointValue;
}

void Food::setPointValue(int value_in)
{
	pointValue = value_in;
}

void Food::resetScore()
{
	score = -1;
}