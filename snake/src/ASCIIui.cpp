#include "ASCIIui.h"
#include <iostream>

/*
	

*/

const int FPS = 30;
SDL_Renderer * ASCIIui::renderer = nullptr;
TTF_Font * ASCIIui::font = nullptr;
std::unordered_map<char, SDL_Texture*> ASCIIui::letterTextures = {};

ASCIIui::ASCIIui() {}

/* #############################################################################################
	
*/
void ASCIIui::init(const char* title, int width, int height, int size, int fps)
{
	textSize = size;
	HEIGHT = height;
	WIDTH = width;
	frameNum = 0;

	letterTextures.reserve(487);

	//Initialize SDL2
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * textSize, height * textSize, 0);

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}

		running = true;
	}
	//Initialize True text front reader
	if (TTF_Init() == 0) 
	{
		font = TTF_OpenFont("data/arial.ttf", size);
		if (font == nullptr)
		{
			std::cout << "TTF_OpenFont() says: \"" << TTF_GetError() << "\" \n";
		}
	}

	//Framesetup
	FPS = fps;
	frameDelay = 1000 / FPS;

	//Populate character vector. Preserves "grid" of monospace letters
	for(int x = 0; x < WIDTH; x++)
		for (int y = 0; y < HEIGHT; y++)
		{
			Letter a = {' '};
			a.move(x*size + 2, y*size);
			characters.push_back(a);
		}
}

/* #############################################################################################

*/
void ASCIIui::quit()
{
	running = false;
}

/* #############################################################################################

*/
void ASCIIui::update()
{
	render();
}

/* #############################################################################################

*/
void ASCIIui::render()
{
	SDL_RenderClear(renderer);

	for (Letter &c : characters)
	{
		SDL_RenderCopy(renderer, c.getTexture(), NULL, &c.getDestRect());
	}	

	//SDL_RenderCopy(renderer, testTex, NULL, NULL);
	SDL_RenderPresent(renderer);
}

/* #############################################################################################

*/
void ASCIIui::clean()
{
	for (std::pair<char, SDL_Texture*> t : letterTextures)
	{
		SDL_DestroyTexture(t.second);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_Quit();
}

/* #############################################################################################

*/
bool ASCIIui::isRunning()
{
	return running;
}

/* #############################################################################################

*/
SDL_Texture* ASCIIui::loadCharTexture(const char c, SDL_Color color)
{
	
	if (letterTextures.count(c) == 1)
	{
		return letterTextures[c];
	}
	else
	{
		//Create texture
		SDL_Surface* surface = TTF_RenderGlyph_Solid(font, c, color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(ASCIIui::renderer, surface);
		SDL_FreeSurface(surface);
		//Add to hash and return
		letterTextures[c] = texture;
		return texture;
	}
}

/* #############################################################################################
	Call at front of main loop to setup framedelay and preserve fps
*/
void ASCIIui::setFrameStart()
{
	frameStart = SDL_GetTicks();
	frameNum++;
}

/* #############################################################################################
	Call at end of main loop to preserve fps
*/
void ASCIIui::setFrameDelay()
{
	frameTime = SDL_GetTicks() - frameStart;
	if (frameDelay > frameTime)
	{
		SDL_Delay(frameDelay - frameTime);
	}
}

/* #############################################################################################
	int x:	x coordinate of character being edited
	int y:	y coordinate of character being edited
	char c: new value for character being edited
*/
void ASCIIui::setLetter(int x, int y, char c)
{
	//Find which character it is
	unsigned int index = y + HEIGHT * x;
	if((!(index >= characters.size())) && !(index < 0))
		characters.at(index).setChar(c);
}

//Clears the board
void ASCIIui::clear(int xStart, int yStart, int xEnd, int yEnd)
{
	for(int x = xStart; x < xEnd; x++)
		for (int y = yStart; y < yEnd; y++)
		{
			setLetter(x, y, ' ');
		}
}

unsigned int ASCIIui::getFrameNum()
{
	return frameNum;
}