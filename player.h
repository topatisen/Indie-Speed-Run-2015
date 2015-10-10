//Player Header
#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class cPlayer
{
	public:
	float x, y, vspeed, hspeed;
	
	bool walkRight, walkLeft, walkUp, walkDown;
	void create()
	{
		walkRight, walkLeft, walkDown, walkUp = false;
		x = 0;
		y = 0;
		//Create Code
	}
	void run(SDL_Event event)
	{
		//Logic code
		
		if(walkRight == true)
		{
			x ++;
		}
		if(walkLeft == true)
		{
			x --;
		}
		if(walkUp == true)
		{
			y --;
		}
		if(walkDown == true)
		{
			y ++;
		}
		//KEYPRESSTEST
		while (SDL_PollEvent(&event)) {
			//Kepresses, works like a charm! <3<3<3<3<3
			switch(event.type){
				case SDL_KEYDOWN:
					if(event.key.keysym.sym==SDLK_w)
					{
						walkUp = true;
						break;
					}
					if(event.key.keysym.sym==SDLK_a)
					{
						walkLeft = true;
						break;
					}
					if(event.key.keysym.sym==SDLK_s)
					{
						walkDown = true;
						break;
					}
					if(event.key.keysym.sym==SDLK_d)
					{
						walkRight = true;
						break;
					}
				case SDL_KEYUP:
					if(event.key.keysym.sym==SDLK_w)
					{
						walkUp = false;
						break;
					}
					if(event.key.keysym.sym==SDLK_a)
					{
						walkLeft = false;
						break;
					}
					if(event.key.keysym.sym==SDLK_s)
					{
						walkDown = false;
						break;
					}
					if(event.key.keysym.sym==SDLK_d)
					{
						walkRight = false;
						break;
					}
			}	
		}
	}
	void draw(SDL_Renderer *ren, SDL_Texture *sPlayer)
	{
		//Draw Code
		renderTexture(sPlayer, ren, x, y);
	}
};

#endif