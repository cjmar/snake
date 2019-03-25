#include "Letter.h"
#include "ASCIIui.h"
#include <iostream>

Letter::Letter(){}
/* #############################################################################################
	
*/
Letter::Letter(char c)
{
	value = c;
	color = { 255, 255, 255, 255 };
	texture = ASCIIui::loadCharTexture(value, color);

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	dRect = { 0, 0, texW, texH };
}

/* #############################################################################################
	Returns Letter texture pointer
*/
SDL_Texture* Letter::getTexture()
{
	return texture;
}

Letter::~Letter(){}

/* #############################################################################################
	Returns Letter destination rect
	dRect = {xcoord, ycoord, width, height}
*/
SDL_Rect& Letter::getDestRect()
{
	return dRect;
}

/* #############################################################################################
	Moves letter using pixel accuracy
*/
void Letter::move(int x, int y)
{
	dRect.x = x;
	dRect.y = y;
}

/* #############################################################################################

*/
void Letter::setChar(char c)
{
	value = c;
	texture = ASCIIui::loadCharTexture(value, color);
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	dRect = { dRect.x, dRect.y, texW, texH };
}