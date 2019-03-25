#ifndef LETTER_H
#define LETTER_H

#include "SDL2/SDL_ttf.h"

class Letter
{
public:
	Letter();
	Letter(char);
	~Letter();

	SDL_Rect& getDestRect();
	SDL_Texture* getTexture();
	void move(int, int);
	void setChar(char);

private:
	char value;
	SDL_Color color;
	SDL_Texture* texture;
	
	SDL_Rect dRect;
};

#endif