//Player Header
#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class cPlayer
{
	public:
	float x, y, vspeed, hspeed, enemyX, enemyY;
	
	bool walkRight, walkLeft, walkUp, walkDown;
	bool colRight, colLeft, colUp, colDown;//col = collision
	void create()
	{
		walkRight = false;
		walkLeft = false;
		walkUp = false;
		walkDown = false;
		x = 300;
		y = 250;
		vspeed = 0;
		hspeed = 0;
		//Create Code
	}
	
	void checkCollision(float x2, float y2)
	{
		//Check left side
		enemyX = x2 ;
		enemyY = y2 ;
		if(x+32 > enemyX&&x+32 < enemyX+4&&y+30 > enemyY&&y< enemyY+32)
		{
				hspeed = -0.5;
		}
		//Check right side
		if(x < enemyX+32&&x > enemyX+28&&y+30 > enemyY&&y< enemyY+32)
		{
			hspeed = 0.5;
		}
		//Check Up
		if(x+32 > enemyX&&x < enemyX+32&&y<enemyY+32&&y>enemyY+28)
		{
				vspeed = 0.5;
		}
		//Check Down
		if(x+32 > enemyX&&x < enemyX+30&&y+32 > enemyY&&y+32<enemyY+4)
		{
			vspeed = -0.5;
		}
	}
	void run(SDL_Event event)
	{
		//FRICTION FIXING
		if(hspeed > 0)
			hspeed -= 0.1;
		if(hspeed < 0)
			hspeed += 0.1;
		if(vspeed < 0)
			vspeed += 0.1;
		if(vspeed > 0)
			vspeed -= 0.1;
		//Logic code
		x += hspeed;
		y += vspeed;
		if(walkRight == true)
		{
				hspeed = 1;
		}
		if(walkLeft == true)
		{
				hspeed = -1;
		}
		if(walkUp == true)
		{
			vspeed = -1;
		}
		if(walkDown == true)
		{
				vspeed = 1;
		}
		//Collision
		if(colUp == true)
		{
			y -= 2;
			colUp = false;
		}
		if(colDown == true)
		{
			y += 2;
			colDown = false;
		}
		if(colRight == true)
		{
			x -= 2;
			colRight = false;
		}
		if(colLeft == true)
		{
			x += 2;
			colLeft = false;
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
						vspeed = 0;
						break;
					}
					if(event.key.keysym.sym==SDLK_a)
					{
						hspeed = 0;
						walkLeft = false;
						break;
					}
					if(event.key.keysym.sym==SDLK_s)
					{
						vspeed = 0;
						walkDown = false;
						break;
					}
					if(event.key.keysym.sym==SDLK_d)
					{
						hspeed = 0;
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