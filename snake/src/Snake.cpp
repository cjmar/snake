#include "Snake.h"

//Size of "movement" queue. Queues up actions for quick turns (implemented as stack)
int MAX_MOVEMENTS = 2;

Snake::Snake(int x, int y, std::pair<int, int> direct_in)
{
	direction = direct_in;

	//Start snake at 3 body parts in length
	std::pair<int, int> b1 = {x, y};
	std::pair<int, int> b2 = {x - 1, y};
	std::pair<int, int> b3 = {x - 2, y};
	body.push_back(b1);
	body.push_back(b2);
	body.push_back(b3);

	alive = true;
}

void Snake::reset()
{
	body.clear();
	direction = std::make_pair(1, 0);

	int x = boardEndX / 5;
	int y = boardEndY / 2;

	std::pair<int, int> b1 = { x, y };
	std::pair<int, int> b2 = { x - 1, y };
	std::pair<int, int> b3 = { x - 2, y };
	body.push_back(b1);
	body.push_back(b2);
	body.push_back(b3);

	alive = true;
}

bool Snake::isAlive()
{
	return alive;
}

void Snake::setBoardDim(int sX, int sY, int eX, int eY)
{
	boardStartX = sX;
	boardEndX = eX;
	boardStartY = sY;
	boardEndY = eY;
}

std::vector<std::pair<int, int>> Snake::getBody()
{
	return body;
}

void Snake::move()
{
	for (int i = body.size() - 1; i != 0; i--)
	{
		body[i].first = body[i - 1].first;
		body[i].second = body[i - 1].second;
	}

	body[0].first += direction.first;
	body[0].second += direction.second;

	alive = hitDetect();
}

/*
	Check hit detection on self and board dimensions
*/
bool Snake::hitDetect()
{
	bool a = true;
	int xpos = body[0].first;
	int ypos = body[0].second;
	//snake->setBoardDim(1, 4, width - 1, height - 1);
	if (xpos <= boardStartX - 1 || ypos <= boardStartY - 1 || xpos >= boardEndX || ypos >= boardEndY)
	{
		a = false;
	}

	//Make sure head isnt impacting the body anywhere
	for (int i = body.size() - 1; i != 0; i--)
	{
		if (body[0].first == body[i].first && body[0].second == body[i].second)
		{
			a = false;
			break;
		}
	}

	return a;
}

void Snake::hitFood()
{
	int size = body.size() - 1;
	std::pair<int, int> newEnd = std::make_pair(body.at(size).first, body.at(size).second);
	body.push_back(newEnd);
}

void Snake::setDirection(std::pair<int, int> direct_in)
{
	if (movements.size() >= MAX_MOVEMENTS)
		movements.pop();
		
	movements.push(direct_in);
	direction = movements.top();
}