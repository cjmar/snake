#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <stack>

class Snake
{
public:
	Snake(int, int, std::pair<int, int>);
	std::vector<std::pair<int, int>> getBody();
	void setBoardDim(int, int, int, int);
	void setDirection(std::pair<int, int>);
	void move();
	bool isAlive();
	void hitFood();
	void reset();

private:
	bool alive;
	bool hitDetect();

	int boardStartX;
	int boardEndX;
	int boardStartY;
	int boardEndY;

	std::vector<std::pair<int, int>> body;
	std::pair<int, int> direction;
	std::stack<std::pair<int, int>> movements;
	int addDirections(std::pair<int, int>, std::pair<int, int>);
};

#endif