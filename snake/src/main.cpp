//#define SDL_MAIN_HANDLED

#include <Windows.h>
#include "ASCIIui.h"
#include <string>

//Snake
#include "Game.h"

ASCIIui* app = nullptr;
Game game;

    ///*
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
	//*/
//int main(int argc, char**argv)
{
	//SDL_SetMainReady();
	int FPS = 30;
	int width = 28;
	int height = 18;
	int textSize = 15;

	app = new ASCIIui();

	//Title, Width (in chars), height (in chars), text size, FPS
	app->init("ASCII Snake", width, height, textSize, FPS);
	//app.init("ASCII Console", 34, 18, 30, FPS);

	//Initialize game
	game.init(width, height, app);

	while (app->isRunning())
	{
		app->setFrameStart();
		app->clear(1, 4, width - 1, height - 1);
		//Make your own event handler (eventually add a callback?)
		game.eventHandle();
		game.update();
		app->update();
		app->setFrameDelay();
	}

	app->clean();
	app = nullptr;
	delete app;

	return 0;
}