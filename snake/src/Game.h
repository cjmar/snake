#ifndef GAME_H
#define GAME_H

/*	Rules of the game

	Use WASD to move the snake around
	WASD will also control menu options if implemented
	Esc will pause or hard reset the game
	Space will begin a game
	To grow the snake, you must eat an apple '@'
		Eating an apple grows the snake by one unit

	You can also eat a flower '*'
		Eating an flower will not grow the snake

	When a user eats something, they score points
		Apple = 1 point
		Flower = 5 points;

	As the game ticks by, the snake gets faster (logarithmic scaling)
	The snakes minimum speed is also altered by its current size (lightly)
	Speed formula is untested
		Speed =  MaxSpeed * log(size) / log(max size (width * height))
	Eating an apple decreases the current speed
		Decreased speed formula is untested (needs to be atleast a little "fun")
		Speed = Speed - baseSpeed / 3 (a third of minimum speed)
	Eating a flower does not alter speed

	An apple is always on the map
	An other is generated some time after an apple placed on the map
		Quickly at start, then slowly as game length increased (up to a couple seconds)

	If a player wishes to maximize their score, they must collect the others

	The game ends when the players snake takes up the entire board
	The top 10 scores will be displayed at the end of a game
		Stored in a binary file to reduce ability to alter using a simple text editor
*/

#include "ASCIIui.h"
#include <vector>
#include <string>
#include "Snake.h"
#include "Food.h"

class Game
{
public:
	enum Game_State //Game state for menu selection/messages
	{
		//GameStartInfo -> GameOngoing -> gamewon/gamelost -> GameStartInfo -> GameOngoing -> ...
		GameStartInfo,
		GameOngoing,
		GameWon,
		GameLost,	
	};

	Game();
	~Game();
	void init(int, int, ASCIIui*);
	void update();
	void eventHandle();
	void setMessageTop(std::string, int, bool);
	void setMessageMiddle(std::string, int);

private:
	int width;
	int height;
	int tickRate;
	int tick;
	Game_State gameState;

	bool toggle;

	void drawMap();
	void showScoreScreen(std::string);
	void recordScore(bool);
	void loadBinaryFile();

	int scores[4];
	std::vector < std::vector<char>> map;
	ASCIIui* appPtr;
	Snake* snake;
	Food* food;
};

#endif