//Player Header
#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//Block class
class cBlock
{
	public:
		int x, y,basecol,color1, color2, color3, life;
		bool alive, looseLife;
	void create(float x1, float y1,int col1, int col2, int col3 )
	{
		life = 12;
		alive = true;
		looseLife = true;
		color1 = col1+pRand()%19+1;
		color2 = col2+pRand()%19+1;
		color3 = col3+pRand()%19+1;
		x = x1;
		y = y1;
		x = x - (x%32);
		y = y - (y%32);
	}
	
	void run()
	{
		//Maybe not needed
	}
	void checkCollision(float otherx, float othery)
	{
		if(sqrt((otherx-x+8)*(otherx-x+8)+(othery-y)*(othery-y))<(24))
		{
			
				life -= 1;
			
			if(life < 0)
			alive = false;
		}
	}
	void draw(SDL_Renderer *ren, SDL_Texture *sBlock)
	{
		if(x > 768)
		alive = false;
		if(x < -768)
		alive = false;
		if(y > 600)
		alive = false;
		if(y < -600)
		alive = false;
		if(alive == true)
		{
		SDL_SetTextureColorMod(sBlock,
                           color1,
                           color2,
                           color3);
			renderTexture(sBlock, ren, x+viewx, y+viewy);
			
		}
	}
};

//Block creator, 
//Enemytest class
class cEnemy
{
	public:
		float x, y, vspeed, hspeed, color1, color2, color3,dx, dy;
		int stColR,stColG,stColB;
				
				
		bool alive;
		bool hit;
		bool addColor, addToAmount;
	void create(float startx, float starty, float col1, float col2, float col3)
	{
		addToAmount = false;
		enemyAmount ++;
		color1 = 255;
		color2 = 255;
		color3 = 255;
		color1 = col1;
		color2 = col2;
		color3 = col3;
		stColR = color1;
		stColG = color2;
		stColB = color3;
		x = startx;
		y = starty;
		hspeed = 0;
		vspeed = 0;
		addColor = false;
		alive = true;
		hit = false;
	}
	void run(float targetx, float targety)
	{
		if(stColR > 254)
			stColR = 254;
		if(stColG > 254)
			stColG = 254;
		if(stColB > 254)
			stColB = 254;
		if(x > 832)
		alive = false;
		if(x < -832)
		alive = false;
		if(y > 632)
		alive = false;
		if(y < -632)
		alive = false;
		if(alive == false)
		{
			if(addToAmount == false)
			{
				enemyCheck ++;
				addToAmount = true;
			}
		}
		if((color1 < 2)&&(color2 < 2)&&(color3 < 2))
		{
			alive = false;
		}
		if(alive == false)
		{
			x = -6000;
		}
		if(alive == true){
		if(x < -800)
		hspeed = 3;
		if(x > 1600)
		hspeed = -3;
		if(y < -600)
		vspeed = 3;
		if(y > 1600)
		vspeed = -3;
		if(hspeed > 1)
		hspeed = 1;
		if(hspeed < -1)
		hspeed = -1;
		if(vspeed > 1)
		vspeed = 1;
		if(vspeed < -1)
		vspeed = -1;
		if(sqrt((targetx-x)*(targetx-x)+(targety-y)*(targety-y))<(24))
		{
			playerHealth -= 20;
			if(addColor == false)
			{
			
			if(globR < 255)
			{
				globR += stColR*0.1;
			}
			if(globG < 255)
			{
				globG += stColG*0.1;
			}
			if(globB < 255)
			{
				globB += stColB*0.1;
			}
				
				addColor = true;
				
			}
			else
			{
				alive = false;
			}
			
		}
		if(sqrt((targetx-x)*(targetx-x)+(targety-y)*(targety-y))<(600))
		{
		if(x+8 > targetx)
		{
			hspeed -= 0.25;
		}
		if(x+8 < targetx)
		{
			hspeed += 0.25;
		}
		if(y+8 < targety)
		{
			vspeed += 0.25;
		}
		if(y+8 > targety)
		{
			vspeed -= 0.25;
		}
		}
		x +=hspeed;
		y +=vspeed;
		}
		else
		{
			x = -6000;
			y = -6000;
		}

	}
	//collision with other enemies
	void checkCollision(float otherx, float othery,float otherradius)
	{
		if(sqrt((otherx-x)*(otherx-x)+(othery-y)*(othery-y))<(8+otherradius)) 
		{
			
			if(x >= otherx)
			hspeed += ((otherx-x)*(otherx-x)/80);
			if(x <= otherx)
			hspeed -= ((otherx-x)*(otherx-x)/80);
			if(y >= othery)
			vspeed += ((othery-y)*(othery-y)/80);
			if(y <= othery)
			vspeed -= ((othery-y)*(othery-y)/80);
		}
	}
	//collision with other bullets
	void checkCollisionBullet(float otherx, float othery,float otherradius)
	{
		if(sqrt((otherx-x)*(otherx-x)+(othery-y)*(othery-y))<(4+otherradius)) 
		{
			hit = true;
			if(globR > 1)
			{
				color1 -= 20;
			}
			if(globG > 1)
			{
				color2 -= 20;
			}
			if(globB > 1)
			{
				color3 -= 20;
			}
			/*if(x >= otherx)
			hspeed += ((otherx-x)*(otherx-x)/80);
			if(x <= otherx)
			hspeed -= ((otherx-x)*(otherx-x)/80);
			if(y >= othery)
			vspeed += ((othery-y)*(othery-y)/80);
			if(y <= othery)
			vspeed -= ((othery-y)*(othery-y)/80);*/
		}
	}
	void draw(SDL_Renderer *ren, SDL_Texture *sEnemy)
	{
		if(alive == true)
		{
		SDL_SetTextureColorMod(sEnemy,
                           stColR,
                           stColG,
                           stColB);
			renderTexture(sEnemy, ren, x+viewx, y+viewy);
		
		}
	}
};

class cSpawner
{
	public:
	cEnemy oEnemy[8];
	int enemyAmount;
	void create(float startx, float starty, float col1, float col2, float col3)
	{
		enemyAmount = 8;
		for(int i = 0;i<enemyAmount;i++)
		{
			oEnemy[i].create(startx+(rand()%16),starty+(rand()%16), col1, col2, col3);
		}
	}
	void run(float targetx, float targety)
	{
		
		for(int i = 0;i<enemyAmount;i++)
		{
			oEnemy[i].run(targetx,targety);
		}
		for(int i = 0;i<enemyAmount;i++)
		{
			for(int p = 0;p<enemyAmount;p++)
			{
				oEnemy[i].checkCollision(oEnemy[p].x,oEnemy[p].y,4);
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
class cRoomCreator
{
	public:
	cBlock oBlock[48];
	cSpawner oSpawner;
	int blockAmount, blockNum;
	int blockx, blocky, roomWidth, roomHeight, randDoor, exists;
	int col1, col2, col3, colorType;
	bool topWall, rightWall, downWall, leftWall, roomFinished;
	void create(float x1, float y1)
	{
		topWall = true;
		rightWall = false;
		downWall = false;
		leftWall = false;
		roomFinished = false;
		blockAmount = 48;
		blockNum = 0;
		roomWidth = rand()%12+3;
		roomHeight = roomWidth = rand()%12+3;
		randDoor = (rand()%(roomWidth+roomHeight)+1); 
		blockx = x1;
		blocky = y1;
		colorType = rand()%3+1;
		if(colorType <= 1)
		{
			col1 = 204;
			col2 = 0;
			col3 = 0;
		}
		if(colorType == 2)
		{
			col1 = 0;
			col2 = 204;
			col3 = 0;
		}
		if(colorType >= 3)
		{
			col1 = 0;
			col2 = 0;
			col3 = 204;
		}

		for(int i = 0;i<blockAmount;i++)
		{
		if(colorType <= 1)
		{
			col1 = 204;
			col2 = 0;
			col3 = 0;
		}
		if(colorType == 2)
		{
			col1 = 0;
			col2 = 204;
			col3 = 0;
		}
		if(colorType >= 3)
		{
			col1 = 0;
			col2 = 0;
			col3 = 204;
		}
			oBlock[i].create(blockx+viewx, blocky+viewy,col1,col2,col3);
		}
		oSpawner.create(x1+((roomWidth/2)*32),y1+((roomHeight/2)*32),col1, col2, col3);
	}
	void generateRoom(float targetx, float targety)
	{
	for(int i = 0;i<blockAmount;i++)
		{
			if(oBlock[i].alive == false)
			oBlock[i].x = -6000;
		}
	if(roomFinished == true)
	oSpawner.run(targetx, targety);
	if(roomFinished == false){
		//Start at top left, move in a rectangle, end at start
		if(topWall == true)
		{
			if(blockNum < roomWidth)
			{
				if(blockNum != randDoor)
				{
					oBlock[blockNum].create(blockx, blocky,col1,col2,col3);
				}
				else
				{
					randDoor = (rand()%(roomWidth+roomHeight)+1); 
				}
				
				blockx +=32;
				blockNum ++;
			}
			else
			{
				rightWall = true;
			}
		}
		if(rightWall == true)
		{
			topWall = false; //Stop going right
			if(blockNum < roomHeight+roomWidth)
			{
			if(blockNum != randDoor)
			{
				oBlock[blockNum].create(blockx, blocky,col1,col2,col3);
			}
			else
				{
					randDoor = (rand()%(roomWidth+roomHeight)+1); 
				}
				blocky += 32;
				blockNum ++;
			}
			else
			{
				downWall = true;
			}
		}
		if(downWall == true)
		{
			rightWall = false; //Stop going down
			if(blockNum < roomHeight+(roomWidth*2))
			{
			if(blockNum != randDoor)
			{
				oBlock[blockNum].create(blockx, blocky,col1,col2,col3);
			}
			else
				{
					randDoor = (rand()%(roomWidth+roomHeight)+1); 
				}
				blockx -= 32;
				blockNum ++;
			}
			else
			{
				leftWall = true;
			}
		}
		if(leftWall == true)
		{
			downWall = false; //Stop going down
			if(blockNum < (roomHeight*2)+(roomWidth*2))
			{
			if(blockNum != randDoor)
			{
				oBlock[blockNum].create(blockx, blocky,col1,col2,col3);
			}
			else
				{
					randDoor = (rand()%(roomWidth+roomHeight)+1); 
				}
				blocky -= 32;
				blockNum ++;
			}
			else
			{
				roomFinished = true;
				leftWall = false;
			}
		}
	}
	else
	{
		
	}
	};
	void draw(SDL_Renderer *ren, SDL_Texture *sBlock, SDL_Texture *sEnemy)
	{
		oSpawner.draw(ren, sEnemy);
		for(int i = 0;i<blockNum;i++)
		{
			oBlock[i].draw(ren, sBlock);
		}
	}
	
};


class cMapMaker
{
	public:
		cRoomCreator oRoomCreator[10];
		//cRoomCreator oMainRoom;
	void create()
	{
		playerHealth = 100;
		/*oMainRoom.create(-800,-600);
		oMainRoom.roomWidth = 50;
		oMainRoom.roomHeight = 38;
		oMainRoom.randDoor = 500;*/
		for(int i = 0;i<10;i++)
		{
			oRoomCreator[i].create(-800+(rand()%1599+1),-600+(rand()%1199+1));
		}
	}
	
	void makeMap(float targetx, float targety)
	{
		//oMainRoom.generateRoom(targetx, targety);
		for(int i = 0;i<10;i++)
		{
			oRoomCreator[i].generateRoom(targetx, targety);
		}
	}
	void draw(SDL_Renderer *ren, SDL_Texture *sBlock, SDL_Texture *sEnemy)
	{
		//oMainRoom.draw(ren, sBlock,sEnemy);
		for(int i = 0;i<10;i++)
		{
			oRoomCreator[i].draw(ren, sBlock, sEnemy);
		}
	}
};
#endif
