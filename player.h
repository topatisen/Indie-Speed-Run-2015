//Player Header
#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class cBullet
{
	public:
		float x, y, hspeed, vspeed;
		int color1, color2, color3;
		bool alive, isFired;
	void create()
	{
		isFired = false;
		alive = false;
		x = -6000;
		y = -6000;
		color1 = 0;
		color2 = 0;
		color3 = 0;
	}
	void run()
	{
		if(alive == false)
		{
			x = -6000;
			y = -6000;
		}
		if(x < -800)
		hspeed = 2;
		if(x > 800)
		hspeed = -2;
		if(y < -616)
		vspeed = 2;
		if(y > 600)
		vspeed = -2;
	}
	void shoot(int direction, int col1, int col2, int col3)
	{
		if(isFired == false)
		{
		//direction clockwise starts up 1,2,3,4
		if(direction == 1)
		{
			vspeed = -8;
		}
		if(direction == 2)
		{
			hspeed = 8;
		}
		if(direction == 3)
		{
			vspeed = 8;
		}
		if(direction == 4)
		{
			hspeed = -8;
		}
		color1 = col1;
		color2 = col2;
		color3 = col3;
		isFired = true;
		}
	}
	void draw(SDL_Renderer *ren, SDL_Texture *sBullet)
	{
		renderTexture(sBullet, ren, x+viewx, y+viewy);
		SDL_SetTextureColorMod(sBullet,
                           col1,
                           col2,
                           col3);
	}
};
class cPlayer
{
	public:
	
	//rectangle for healthbar
	SDL_Rect rectOrig;
	SDL_Rect rectNew;
	
	SDL_Rect ammoROrig;
	SDL_Rect ammoRNew;

	SDL_Rect ammoGOrig;
	SDL_Rect ammoGNew;

	SDL_Rect ammoBOrig;
	SDL_Rect ammoBNew;

	float x, y, vspeed, hspeed, enemyX, enemyY;
	int ammoR, ammoG, ammoB;
	bool walkRight, walkLeft, walkUp, walkDown;
	bool colRight, colLeft, colUp, colDown;//col = collision
	void create()
	{
		rectOrig.x = 0;
		rectOrig.y = 0;
		rectOrig.w = 32;
		rectOrig.h = 32;

		ammoR = 0;
		ammoG = 255;
		ammoB = 0;

		ammoRNew.x = 15;
		ammoRNew.y = 15;
		ammoRNew.w = 128;
		ammoRNew.h = 16;
		ammoROrig.x = 0;

		walkRight = false;
		walkLeft = false;
		walkUp = false;
		walkDown = false;
		x = 0;
		y = 0;
		vspeed = 0;
		hspeed = 0;
		//Create Code
	}
	
	void checkCollision(float x2, float y2)
	{
		//Check left side
		enemyX = x2 ;
		enemyY = y2 ;
		if((x+32 > enemyX&&x+32 < enemyX+4&&y+30 > enemyY&&y< enemyY+30))
		{
				hspeed = -0.5;
		}
		//Check right side
		if((x < enemyX+32&&x > enemyX+28&&y+30 > enemyY&&y< enemyY+30))
		{
			hspeed = 0.5;
		}
		//Check Up
		if((x+30 > enemyX&&x < enemyX+30&&y<enemyY+32&&y>enemyY+28))
		{
				vspeed = 0.5;
		}
		//Check Down
		if((x+30 > enemyX&&x < enemyX+30&&y+32 > enemyY&&y+32<enemyY+4))
		{
			vspeed = -0.5;
		}
	}
	void run(SDL_Event event)
	{
		//healthbar
		rectNew.x = x-16+viewx;
		rectNew.y = y-32+viewy;
		rectNew.w = playerHealth*0.64;
		rectNew.h = 16;
		if(playerHealth < 100)
		{
			playerHealth += 0.25;
		}
		////
		if(x < -800)
		hspeed = 2;
		if(x > 800)
		hspeed = -2;
		if(y < -616)
		vspeed = 2;
		if(y > 600)
		vspeed = -2;
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
				hspeed = 2;
		}
		if(walkLeft == true)
		{
				hspeed = -2;
		}
		if(walkUp == true)
		{
			vspeed = -2;
		}
		if(walkDown == true)
		{
				vspeed = 2;
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
	void draw(SDL_Renderer *ren, SDL_Texture *sPlayer, SDL_Texture *sHealthbar)
	{
		//Draw Code
		//healthbar
		SDL_RenderCopyEx(ren, sHealthbar, &rectOrig, &rectNew,0,NULL,SDL_FLIP_NONE);
		SDL_RenderCopyEx(ren, sHealthbar, &ammoROrig, &ammoRNew,0,NULL,SDL_FLIP_NONE);
		renderTexture(sPlayer, ren, x+viewx, y+viewy);
		SDL_SetTextureColorMod(sPlayer,
                           ammoR,
                           ammoG,
                           ammoB);
	}
};

#endif
