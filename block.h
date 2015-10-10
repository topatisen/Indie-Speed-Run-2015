//Player Header
#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//Block class
class cBlock
{
	public:
		int x, y;
	void create(float x1, float y1)
	{
		
		x = x1;
		y = y1;
		x = x - (x%32);
		y = y - (y%32);
	}
	
	void run()
	{
		//Maybe not needed
	}
	
	void draw(SDL_Renderer *ren, SDL_Texture *sBlock)
	{
		renderTexture(sBlock, ren, x+viewx, y+viewy);
	}
};

//Block creator, 

class cRoomCreator
{
	public:
	cBlock oBlock[48];
	int blockAmount, blockNum;
	int blockx, blocky, roomWidth, roomHeight, randDoor, exists;
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
		roomWidth = rand()%12+1;
		roomHeight = roomWidth = rand()%12+1;
		randDoor = (rand()%(roomWidth+roomHeight)+1); 
		blockx = x1;
		blocky = y1;
		for(int i = 0;i<blockAmount;i++)
		{
			oBlock[i].create(blockx+viewx, blocky+viewy);
		}
	}
	void generateRoom()
	{
	if(roomFinished == false){
		//Start at top left, move in a rectangle, end at start
		if(topWall == true)
		{
			if(blockNum < roomWidth)
			{
				if(blockNum != randDoor)
				{
					oBlock[blockNum].create(blockx, blocky);
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
				oBlock[blockNum].create(blockx, blocky);
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
				oBlock[blockNum].create(blockx, blocky);
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
				oBlock[blockNum].create(blockx, blocky);
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
				roomFinished = false;
				leftWall = false;
			}
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


class cMapMaker
{
	public:
		cRoomCreator oRoomCreator[10];
	void create()
	{
		for(int i = 0;i<10;i++)
		{
			oRoomCreator[i].create(-800+rand()%1599+1,-600+rand()%1199+1);
		}
	}
	
	void makeMap()
	{
		for(int i = 0;i<10;i++)
		{
			oRoomCreator[i].generateRoom();
		}
	}
	void draw(SDL_Renderer *ren, SDL_Texture *sBlock)
	{
		for(int i = 0;i<10;i++)
		{
			oRoomCreator[i].draw(ren, sBlock);
		}
	}
};
#endif