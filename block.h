//Player Header
#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//Block class
class cBlock
{
	public:
		float x, y;
	void create(float x1, float y1)
	{
		x = x1;
		y = y1;
	}
	
	void run()
	{
		//Maybe not needed
	}
	
	void draw(SDL_Renderer *ren, SDL_Texture *sBlock)
	{
		renderTexture(sBlock, ren, x, y);
	}
};
/*
class cRoom
{
	public:
	cBlock oBlock[48];
	int blockAmount, blockNum;
	int blockx, blocky, roomWidth, roomHeight;
	int typeChance, corridorExists, corridorSide;
	bool topWall, rightWall, downWall, leftWall;
	/*Psuedo
Slumpa om korridor eller rum, slumpa storlek/längd
bool som säger korridor eller stopp.
slumpar position för korridoröppning eller inte
Blockcreator använder för att generera nästa rum/korridor


	void create()
	{
		//slumpa korridor eller rum
		typeChance = rand()%2+1;
		if(typeChance == 1)//korridor
		{
			roomWidth = 3;
			roomHeight = 3+(rand()%12+1);
		}
		else
		{
			roomWidth = 3+(rand()%8+1);
			roomHeight = 3+(rand()%8+1);
		}
		if(typeChance == 0)//om rum, slumpa chans för korridor
		{
			corridorExists = rand()%3+1;
		}
		if(corridorExists > 2)
		{
			corridorSide = rand()%4+1;
			if(corridorSide == 1)//corridor at top
			{
				corridorX = 32*(rand()%roomWidth+1);
				corridorY = blocky;
			}
			if(corridorSide == 2)//corridor at right
			{
				corridorX = blockx+(roomWidth*32);
				corridorY = 32*(rand()%roomHeight+1);
			}
			if(corridorSide == 3)//corridor at down
			{
				corridorX = 32*(rand()%roomWidth+1);
				corridorY = blocky+(roomHeight*32);
			}
			if(corridorSide == 4)//corridor at left
			{
				corridorX = blockx;
				corridorY = blocky+(roomHeight*32);
			}
		}
		//om korridor, slumpa på ett sätt, om rum, slumpa på annat sätt
		
		
		
		topWall = true;
		rightWall = false;
		downWall = false;
		leftWall = false;
		blockAmount = 48;
		blockNum = 0;
		blockx = 260;
		blocky = 200;
	}
	void generateRoom()
	{
		//Start at top left, move in e rectangle, end at start
		if(topWall == true)
		{
			if(blockNum < roomWidth)
			{
				oBlock[blockNum].create(blockx, blocky);
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
				oBlock[blockNum].create(blockx, blocky);
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
				oBlock[blockNum].create(blockx, blocky);
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
				oBlock[blockNum].create(blockx, blocky);
				blocky -= 32;
				blockNum ++;
			}
			else
			{
				leftWall = false;
			}
		}
	};

};*/
//Block creator, also dungeongenerator
class cBlockCreator
{
	public:
	cBlock oBlock[48];
	int blockAmount, blockNum;
	int blockx, blocky, roomWidth, roomHeight;
	int typeChance, corridorExists, corridorSide;
	bool topWall, rightWall, downWall, leftWall;
	void create()
	{
		//corridorChance = rand()%4+1;
		//corridorLength = rand()%4+1;
		topWall = true;
		rightWall = false;
		downWall = false;
		leftWall = false;
		blockAmount = 100;
		blockNum = 0;
		roomWidth = 10;
		roomHeight = 1;
		blockx = 260;
		blocky = 200;
	}
	void generateRoom()
	{
		//Start at top left, move in e rectangle, end at start
		if(topWall == true)
		{
			if(blockNum < roomWidth)
			{
				oBlock[blockNum].create(blockx, blocky);
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
				oBlock[blockNum].create(blockx, blocky);
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
				oBlock[blockNum].create(blockx, blocky);
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
				oBlock[blockNum].create(blockx, blocky);
				blocky -= 32;
				blockNum ++;
			}
			else
			{
				leftWall = false;
			}
		}
	};
	void draw(SDL_Renderer *ren, SDL_Texture *sBlock)
	{
		for(int i = 0;i<blockNum;i++)
		{
			oBlock[i].draw(ren, sBlock);
		}
	}
	
};
#endif