#ifndef ASCII_UI_H
#define ASCII_UI_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "Letter.h"
#include <vector>
#include <unordered_map>

class ASCIIui
{
public:
	ASCIIui();
	void init(const char*, int, int, int, int);
	bool isRunning();
	void quit();
	void clean();
	void update();
	void render();
	void clear(int, int, int, int);
	unsigned int getFrameNum();

	void setFrameStart();
	void setFrameDelay();
	void setLetter(int, int, char);

	static SDL_Texture* loadCharTexture(char, SDL_Color);
	static TTF_Font* font;
	static SDL_Renderer* renderer;

private:
	//Frame data
	int FPS;
	int frameDelay;
	Uint32 frameStart;
	int frameTime;
	unsigned int frameNum;

	//List of every ASCII character being used on the grid
	std::vector<Letter> characters;
	//Storage for textures so they're only created once
	static std::unordered_map<char, SDL_Texture*> letterTextures;

	int textSize;
	SDL_Window * window;
	bool running;

	int HEIGHT;
	int WIDTH;
};

#endif