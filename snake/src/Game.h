#ifndef GAME_H
#define GAME_H

/*	Rules of the game

	Use WASD to move the snake around
	WASD will also control menu options if implemented
	Esc will hard reset the game
	Space will begin a game
	To grow the snake, you must eat an apple '@'
		Eating an apple grows the snake by one unit

	When a user eats an apple, they score points
		Apple = 1 point

	An apple is always on the map

	If a player wishes to maximize their score, they must collect the others

	The game ends when the players snake takes up the entire board
	The top 3 scores will be displayed at the end of a game
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