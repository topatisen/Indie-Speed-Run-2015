//Player Header
#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class cPlayer
{
	public:
	float x, y, vspeed, hspeed;
	
	void create()
	{
		//Create Code
	}
	void run()
	{
		//Logic code
	}
	void draw(SDL_Renderer *ren, SDL_Texture *sPlayer)
	{
		//Draw Code
		renderTexture(sPlayer, ren, 400, 300);
	}
};

#endif