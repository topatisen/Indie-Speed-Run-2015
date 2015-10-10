//Player Header
#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//Enemytest class
class cEnemy
{
	public:
		float x, y, vspeed, hspeed, col1, col2, col3,
				dx, dy;
	void create(float startx, float starty)
	{
		col1 = 128;
		col2 = 32;
		col3 = 0;
		x = startx;
		y = starty;
		hspeed = 0;
		vspeed = 0;
	}
	void run(float targetx, float targety)
	{
		if(sqrt((targetx-x)*(targetx-x)+(targety-y)*(targety-y))<(64))
		{
		if(x > targetx)
		{
			hspeed =-2;
		}
		if(x < targetx)
		{
			hspeed = 2;
		}
		if(y < targety)
		{
			vspeed = 2;
		}
		if(y > targety)
		{
			hspeed = -2;
		}
		}
		x +=hspeed;
		y +=vspeed;
		if(hspeed < 0.5&&hspeed > -0.5)
		hspeed = 0;
		if(vspeed < 0.5&&vspeed > -0.5)
		vspeed = 0;
		if(hspeed > 0)
		hspeed -= 0.5;
		if(hspeed < 0)
		hspeed += 0.5;
		if(vspeed > 0)
		vspeed -= 0.5;
		if(vspeed < 0)
		vspeed += 0.5;
	}
	//collision with other enemies
	void checkCollision(float otherx, float othery)
	{
		if(sqrt((otherx-x)*(otherx-x)+(othery-y)*(othery-y))<( 8)) 
		{
			if(x >= otherx)
			hspeed += ((otherx-x)*(otherx-x)/1000);
			if(x <= otherx)
			hspeed -= ((otherx-x)*(otherx-x)/1000);
			if(y >= othery)
			vspeed += ((othery-y)*(othery-y)/1000);
			if(y <= othery)
			vspeed -= ((othery-y)*(othery-y)/1000);
		}
	}
	void draw(SDL_Renderer *ren, SDL_Texture *sEnemy)
	{
			renderTexture(sEnemy, ren, x+viewx, y+viewy);
		SDL_SetTextureColorMod(sEnemy,
                           col1,
                           col2,
                           col3);
	}
};

class cSpawner
{
	public:
	cEnemy oEnemy[300];
	int enemyAmount;
	void create()
	{
		enemyAmount = 300;
		for(int i = 0;i<enemyAmount;i++)
		{
			oEnemy[i].create(300+(rand()%16),200+(rand()%16));
		}
	}
	void run(float targetx, float targety)
	{
		
		for(int i = 0;i<enemyAmount;i++)
		{
			oEnemy[i].run(targetx,targety);
		}
		//Checkcollision
		for(int i = 0;i<enemyAmount;i++)
		{
			for(int p = 0;p<enemyAmount;p++)
			{
				oEnemy[i].checkCollision(oEnemy[p].x,oEnemy[p].y);
			}
		}
	}
	void draw(SDL_Renderer *ren, SDL_Texture *sEnemy)
	{
		for(int i = 0;i<enemyAmount;i++)
		{
			oEnemy[i].draw(ren,sEnemy);
		}
	}
};
class cPlayer
{
	public:
	
	//rectangle for healthbar
	SDL_Rect rectOrig;
	SDL_Rect rectNew;
	
	float x, y, vspeed, hspeed, enemyX, enemyY, health;
	int ammoR, ammoG, ammoB;
	bool walkRight, walkLeft, walkUp, walkDown;
	bool colRight, colLeft, colUp, colDown;//col = collision
	void create()
	{
		rectOrig.x = 0;
		rectOrig.y = 0;
		rectOrig.w = 32;
		rectOrig.h = 32;
		rectNew.x = 0;
		rectNew.y = 0;
		rectNew.w = 128;
		rectNew.h = 16;
		health = 0;
		ammoR = 0;
		ammoG = 255;
		ammoB = 0;
		walkRight = false;
		walkLeft = false;
		walkUp = false;
		walkDown = false;
		x = 260;
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
		rectNew.w = health*0.64;
		rectNew.h = 16;
		if(health < 100)
		{
			health += 0.5;
		}
		////
		
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
		renderTexture(sPlayer, ren, x+viewx, y+viewy);
		SDL_SetTextureColorMod(sPlayer,
                           ammoR,
                           ammoG,
                           ammoB);
	}
};

#endif