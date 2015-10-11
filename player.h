//Player Header
#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class cBullet
{
	public:
		float x, y, hspeed, vspeed;
		int color1, color2, color3, direction;
		bool alive, isFired, collision;
	void create()
	{
		isFired = false;
		collision = false;
		alive = false;
		x = -6000;
		y = -6000;
		color1 = 0;
		color2 = 0;
		color3 = 0;
	}
	void run()
	{
		x +=hspeed;
		y +=vspeed;
		if(alive == false)
		{
			x = -6000;
			y = -6000;
		}
		if(x < -800)
		alive = false;
		if(x > 800)
		alive = false;
		if(y < -616)
		alive = false;
		if(y > 600)
		alive = false;
	}
	void checkCollision(float otherx, float othery)
	{
		if(sqrt((otherx-x)*(otherx-x)+(othery-y)*(othery-y))<(24))
		{
			alive = false;
		}
	}
	void shoot(float playerx, float playery, int col1, int col2, int col3)
	{
		alive = true;
		x = playerx;
		y = playery;
		
		//direction clockwise starts up 0,1,2,3
		if(direction == 0)
		{
			vspeed = -8;
			hspeed = 0;
		}
		if(direction == 1)
		{
			hspeed = 8;
			vspeed = 0;
		}
		if(direction == 2)
		{
		
			hspeed = 0;
			vspeed = 8;
		}
		if(direction == 3)
		{
			hspeed = -8;
			vspeed = 0;
		}
		color1 = col1;
		color2 = col2;
		color3 = col3;

	}
	void draw(SDL_Renderer *ren, SDL_Texture *sBullet)
	{
		renderTexture(sBullet, ren, x+viewx, y+viewy);
		SDL_SetTextureColorMod(sBullet,
                           color1,
                           color2,
                           color3);
	}
};
class cPlayer
{
	public:
	
	cBullet oBullet[8];
	
	
	//rectangle for healthbar
	SDL_Rect rectOrig;
	SDL_Rect rectNew;
	
	SDL_Rect ammoROrig;
	SDL_Rect ammoRNew;

	SDL_Rect ammoGOrig;
	SDL_Rect ammoGNew;

	SDL_Rect ammoBOrig;
	SDL_Rect ammoBNew;

	char rHex[5];
	char gHex[5];
	char bHex[5];
	SDL_Texture *rHexMessage;
	SDL_Texture *gHexMessage;
	SDL_Texture *bHexMessage;
	float x, y, vspeed, hspeed, enemyX, enemyY;
	int ammoR, ammoG, ammoB, bulletNum, shootingDir, shootTimer;
	bool walkRight, walkLeft, walkUp, walkDown, shooting;
	bool colRight, colLeft, colUp, colDown;//col = collision
	void create()
	{
		shooting = false;
		shootTimer = 0;
		bulletNum = 0;
		for(int i = 0;i<8;i++)
		{
			oBullet[i].create();
		}
		shootingDir = 0;
		
		rectOrig.x = 0;
		rectOrig.y = 0;
		rectOrig.w = 32;
		rectOrig.h = 32;

		rectNew.x = 0;
		rectNew.y = 0;
		rectNew.w = 128;
		rectNew.h = 16;


		ammoR = 173;
		ammoG = 255;
		ammoB = 12;

		ammoRNew.x = 0;
		ammoRNew.y = 0;
		ammoRNew.w = 128;
		ammoRNew.h = 16;

		ammoROrig.x = 0;
		ammoROrig.y = 0;
		ammoROrig.w = 32;
		ammoROrig.h = 32;

		ammoGNew.x = 0;
		ammoGNew.y = 0;
		ammoGNew.w = 128;
		ammoGNew.h = 16;

		ammoGOrig.x = 0;
		ammoGOrig.y = 0;
		ammoGOrig.w = 32;
		ammoGOrig.h = 32;

		ammoBNew.x = 0;
		ammoBNew.y = 0;
		ammoBNew.w = 128;
		ammoBNew.h = 16;

		ammoBOrig.x = 0;
		ammoBOrig.y = 0;
		ammoBOrig.w = 32;
		ammoBOrig.h = 32;

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
		//Bullet
		for(int i = 0;i<8;i++)
		{
			oBullet[i].run();
		}
		if(bulletNum > 7)
		{
			bulletNum = 0;
		}
		//healthbar
		rectNew.x = x-16+viewx;
		rectNew.y = y-32+viewy;
		rectNew.w = playerHealth*0.64;
		rectNew.h = 16;

		// Ammo bars
		// red
		ammoRNew.x = x-64+viewx+284;
		ammoRNew.y = y-64+viewy-96;
		ammoRNew.w = ammoR*0.64;
		ammoRNew.h = 32;
		// green
		ammoGNew.x = x-64+viewx+284;
		ammoGNew.y = y-64+viewy-64;
		ammoGNew.w = ammoG*0.64;
		ammoGNew.h = 32;	
		// blue
		ammoBNew.x = x-64+viewx+284;
		ammoBNew.y = y-64+viewy-32;
		ammoBNew.w = ammoB*0.64;
		ammoBNew.h = 32;	

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
		if(shooting == false)
		{
			shootingDir = 1;
			}
				hspeed = 2;
		}
		if(walkLeft == true)
		{
		if(shooting == false)
		{
			shootingDir = 3;
			}
				hspeed = -2;
		}
		if(walkUp == true)
		{
		if(shooting == false)
		{
			shootingDir = 0;
			}
			vspeed = -2;
		}
		if(walkDown == true)
		{
			if(shooting == false)
			{
				shootingDir = 2;
				}
				vspeed = 2;
		}
		if(shooting == true)
		{
			
			if(shootTimer >6)
			{
				oBullet[bulletNum].direction = shootingDir;
				oBullet[bulletNum].shoot(x,y, ammoR, ammoG, ammoB);
				
				bulletNum ++;
				shootTimer = 0;
			}
			shootTimer ++;
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
					if(event.key.keysym.sym==SDLK_SPACE)
					{
						shooting = true;
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
					if(event.key.keysym.sym==SDLK_SPACE)
					{
						
						shootTimer = 6;
						shooting = false;
						break;
					}
			}	
		}
		sprintf(rHex,"0x%02X",ammoR);
		sprintf(gHex,"0x%02X",ammoG);
		sprintf(bHex,"0x%02X",ammoB);
		
		ammoR = globR;
		ammoG = globG;
		ammoB = globB;
	}
	void draw(SDL_Renderer *ren, SDL_Texture *sPlayer, SDL_Texture *sHealthbar, SDL_Texture *sBullet, SDL_Texture *sRBar, SDL_Texture *sGBar, SDL_Texture *sBBar, TTF_Font *font)
	{
		rHexMessage = createTextMessage(font, {255,255,255}, rHex, ren);
		gHexMessage = createTextMessage(font, {255,255,255}, gHex, ren);
		bHexMessage = createTextMessage(font, {255,255,255}, bHex, ren);
		//Draw Code
		for(int i = 0;i<8;i++)
		{
			oBullet[i].draw(ren,sBullet);
		}
		//healthbar
		SDL_RenderCopyEx(ren, sHealthbar, &rectOrig, &rectNew,0,NULL,SDL_FLIP_NONE);
		// Ammobars
		SDL_RenderCopyEx(ren, sRBar, &ammoROrig, &ammoRNew,0,NULL,SDL_FLIP_NONE);
		SDL_RenderCopyEx(ren, sGBar, &ammoGOrig, &ammoGNew,0,NULL,SDL_FLIP_NONE);
		SDL_RenderCopyEx(ren, sBBar, &ammoBOrig, &ammoBNew,0,NULL,SDL_FLIP_NONE);
		renderTexture(sPlayer, ren, x+viewx, y+viewy);
		SDL_SetTextureColorMod(sPlayer,
                           ammoR,
                           ammoG,
                           ammoB);
		renderTexture(rHexMessage, ren, 630, 136);
		renderTexture(gHexMessage, ren, 630, 166);
		renderTexture(bHexMessage, ren, 630, 196);
		
		SDL_SetTextureColorMod(sRBar,255,0,0);
		SDL_SetTextureColorMod(sGBar,0,255,0);
		SDL_SetTextureColorMod(sBBar,0,0,255);
	}
};

#endif
