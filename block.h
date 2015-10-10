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

//Block creator, also dungeongenerator
class cBlockCreator
{
	public:
	cBlock oBlock[100];
	int blockAmount, blockNum;
	int blockx, blocky, roomWidth, roomHeight;
	bool topWall, rightWall, downWall, leftWall;
	void create()
	{
		topWall = true;
		rightWall = false;
		downWall = false;
		leftWall = false;
		blockAmount = 100;
		blockNum = 0;
		roomWidth = 10;
		roomHeight = 10;
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