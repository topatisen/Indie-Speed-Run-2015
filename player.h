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
		color1 = globR;
		color2 = globG;
		color3 = globB;
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
		if(x < -832)
		alive = false;
		if(x > 832)
		alive = false;
		if(y < -632)
		alive = false;
		if(y > 632)
		alive = false;
	}
	void checkCollision(float otherx, float othery, float radius)
	{
		if(sqrt((otherx-x)*(otherx-x)+(othery-y)*(othery-y))<(8+radius))
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
		if(globR > 1)
		{
			globR -= 1;
		}
		if(globG > 1)
		{
			globG -= 1;
		}
		if(globB > 1)
		{
			globB -= 1;
		}


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
	
	//Player rectangle
	SDL_Rect rPlayerOrig;
	SDL_Rect rPlayerNew;
	
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
		shootingDir = 1;
		walkRight = false;
		walkLeft = false;
		walkUp = false;
		walkDown = false;
		x = 736;
		y = 536;
		vspeed = 0;
		hspeed = 0;
		//Create Code
		rPlayerOrig.x = 0;
		rPlayerOrig.y = 0;
		rPlayerOrig.w = 32;
		rPlayerOrig.h = 32;
		
		rPlayerNew.x = 0;
		rPlayerNew.y = 0;
		rPlayerNew.w = 32;
		rPlayerNew.h = 32;
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
		//player
		rPlayerNew.x = x+viewx;
		rPlayerNew.y = y+viewy;
		rPlayerNew.w = 32;
		rPlayerNew.h = 32;
		
		//healthbar
		rectNew.x = x-16+viewx;
		rectNew.y = y-32+viewy;
		rectNew.w = playerHealth*0.64;
		rectNew.h = 16;

		// Ammo bars
		// red
		ammoRNew.x = x-64+viewx+194;
		ammoRNew.y = y-64+viewy-96;
		ammoRNew.w = ammoR*0.64;
		ammoRNew.h = 16;
		// green
		ammoGNew.x = x-64+viewx+194;
		ammoGNew.y = y-64+viewy-64;
		ammoGNew.w = ammoG*0.64;
		ammoGNew.h = 16;	
		// blue
		ammoBNew.x = x-64+viewx+194;
		ammoBNew.y = y-64+viewy-32;
		ammoBNew.w = ammoB*0.64;
		ammoBNew.h = 16;	

		if(playerHealth < 100)
		{
			playerHealth += 0.25;
		}
		////
		if(x < -768)
		hspeed = 2;
		if(x > 768)
		hspeed = -2;
		if(y < -608)
		vspeed = 2;
		if(y > 608)
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
				hspeed = 3;
		}
		if(walkLeft == true)
		{
		if(shooting == false)
		{
			shootingDir = 3;
			}
				hspeed = -3;
		}
		if(walkUp == true)
		{
		if(shooting == false)
		{
			shootingDir = 0;
			}
			vspeed = -3;
		}
		if(walkDown == true)
		{
			if(shooting == false)
			{
				shootingDir = 2;
				}
				vspeed = 3;
		}
		if(shooting == true)
		{
			
			if(shootTimer >6)
			{
				oBullet[bulletNum].direction = shootingDir;
				oBullet[bulletNum].shoot(x+8,y+8, globR, globG, globB);
				
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
		
		ammoR = globR;
		ammoG = globG;
		ammoB = globB;
		sprintf(rHex,"0x%02X",ammoR);
		sprintf(gHex,"0x%02X",ammoG);
		sprintf(bHex,"0x%02X",ammoB);
	}
	void draw(SDL_Renderer *ren, SDL_Texture *sPlayer, SDL_Texture *sHealthbar, SDL_Texture *sBullet, SDL_Texture *sRBar, SDL_Texture *sGBar, SDL_Texture *sBBar, TTF_Font *font, SDL_Texture *BarLay)
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
		renderTexture(BarLay, ren, 0, 0);
		SDL_RenderCopyEx(ren, sHealthbar, &rectOrig, &rectNew,0,NULL,SDL_FLIP_NONE);
		// Ammobars
		SDL_RenderCopyEx(ren, sRBar, &ammoROrig, &ammoRNew,0,NULL,SDL_FLIP_NONE);
		SDL_RenderCopyEx(ren, sGBar, &ammoGOrig, &ammoGNew,0,NULL,SDL_FLIP_NONE);
		SDL_RenderCopyEx(ren, sBBar, &ammoBOrig, &ammoBNew,0,NULL,SDL_FLIP_NONE);
		if(shootingDir == 0)
			SDL_RenderCopyEx(ren, sPlayer, &rPlayerOrig, &rPlayerNew,180,NULL,SDL_FLIP_NONE);
		if(shootingDir == 1)
			SDL_RenderCopyEx(ren, sPlayer, &rPlayerOrig, &rPlayerNew,270,NULL,SDL_FLIP_NONE);
		if(shootingDir == 2)
			SDL_RenderCopyEx(ren, sPlayer, &rPlayerOrig, &rPlayerNew,0,NULL,SDL_FLIP_NONE);
		if(shootingDir == 3)
			SDL_RenderCopyEx(ren, sPlayer, &rPlayerOrig, &rPlayerNew,90,NULL,SDL_FLIP_NONE);
		//renderTexture(sPlayer, ren, x+viewx, y+viewy);
		
		renderTexture(rHexMessage, ren, 520, 80);
		renderTexture(gHexMessage, ren, 520, 110);
		renderTexture(bHexMessage, ren, 520, 140);
		
		SDL_SetTextureColorMod(sRBar,255,0,0);
		SDL_SetTextureColorMod(sGBar,0,255,0);
		SDL_SetTextureColorMod(sBBar,0,0,255);
	}
};

#endif
