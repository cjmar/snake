#ifndef FOOD_H
#define FOOD_H

#include <vector>

class Food
{
public:
	Food();
	Food(int, int, int, int);
	bool genFood(std::vector<std::pair<int, int>>);
	bool foodOnMap();
	std::pair<int, int> getFoodLoc();
	int getScore();
	void resetScore();
	void setPointValue(int);

private:
	int boardStartX;
	int boardEndX;
	int boardStartY;
	int boardEndY;

	std::pair<int, int> foodLoc;
	void incrementScore();
	int pointValue;
	int score;
};

#endif