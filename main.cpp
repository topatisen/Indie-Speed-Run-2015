/*////////////////////////
SDL-BASE
topatisen
////////////////////////*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <sstream>
#include <string>
#include <random>
#include <stdlib.h>
#include <cstdio>
#include <math.h>
#include "timer.h"

using namespace std;

float viewx = 0;
float viewy = 0;
float playerHealth;
#include "utilities.h"
#include "gamestate.h"
#include "player.h" //player-header
#include "block.h" //block-header, also dungeon generator

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600



const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;




int main(int argc, char *argv[]) {
playerHealth = 0;
std::mt19937 mt(1);
std::uniform_int_distribution<int32_t> intDist(1,2);
mt.max();

	printf("%lu\n", mt);
	printf("%lu\n", mt);
	printf("%lu\n", mt);
	printf("%lu\n", mt);
	printf("%lu\n", mt);
	printf("%lu\n", mt);
	printf("%lu\n", mt);
	//quit-flag
	bool quit;
	//{/* {{{ FPS-limit tjofrees */
	//The frames per second timer
	LTimer fpsTimer;
	//The frames per second cap timer
	LTimer capTimer;
	int countedFrames = 0;
	fpsTimer.start();
	//}/* }}} */
	
	//Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		logSDLError(std::cerr, "SDL_Init");
		return 1;
	}
	TTF_Init();
	IMG_Init(1);
	//{/* {{{ SDL window, renderer'n'shizzle to ma dizzle */
	SDL_Window *window = SDL_CreateWindow("SDL GAME", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == 0){
		logSDLError(std::cerr, "CreateWindow");
		return 2;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (renderer == 0){
		logSDLError(std::cerr, "CreateRenderer");
		return 3;
	}
	//}/* }}} */
	SDL_SetRenderDrawColor(renderer,
                           255,
                           255,
                           255,
                           0);
	
	
	//{/* {{{ Load a font */
	TTF_Font *fFont = NULL;
	fFont = TTF_OpenFont("font.ttf", 24);
	SDL_Color black = {0, 0, 0};
	SDL_Color white = {255, 255, 255};
	//}/* }}} */
	SDL_Texture* msgInfo = createTextMessage(fFont, white, "SDL Base", renderer);
	
	//{/* {{{ SDL event */
	SDL_Event e;
	//}/* }}} */
	
	/* {{{ Textures */
	SDL_Texture *sEnemy = loadTexture("sEnemy.png", renderer);
	SDL_Texture *sRectangle = loadTexture("sRectangle.png", renderer);
	SDL_Texture *sHealthbar = loadTexture("sRectangle.png", renderer);
	SDL_Texture *sPlayer= loadTexture("sRectangle.png", renderer);
	SDL_Texture *sBackground = loadTexture("sBackground.png", renderer);
	SDL_Texture *sMenuOverlay = loadTexture("sMenuOverlay.png", renderer);
	SDL_Texture *sMenuSelector = loadTexture("sMenuSelector.png", renderer);
	SDL_Texture *sAboutOverlay = loadTexture("sAboutOverlay.png", renderer);
	/* }}} */
	
	float avgFPS = 0;
	SDL_Event event;

	cPlayer oPlayer;
	oPlayer.create();
	
	// Gamestate test
	cGameState oGame;
	oGame.create();
	//Block test
	cMapMaker oMapMaker;
	oMapMaker.create();
	
	
	//while not quitting (gameloop)
	while(oGame.state != 4) {
		//fps
		int frameTicks = capTimer.getTicks();
	
		// Empty event queueueueueu
		SDL_PumpEvents();
		
		/* {{{ Keyboard presses, mouse events osv.*/
		const Uint8 *keyboardstate = SDL_GetKeyboardState(NULL);


		
		//Logical, magical!
			
		oGame.run(keyboardstate);
		if(oGame.state ==2)
		{
		oPlayer.run(event);
		
		//run spawner
		
		//check collisions enemies -> blocks
		
		for(int t = 0; t<20;t++)
		{
		for(int p = 0; p<20;p++)
		{
			for(int i = 0; i<48;i++)
			{
				for(int g = 0; g<8;g++)
				{
					oMapMaker.oRoomCreator[p].oSpawner.oEnemy[g].checkCollision(oMapMaker.oRoomCreator[t].oBlock[i].x+8, oMapMaker.oRoomCreator[t].oBlock[i].y+8,24);
				}
			}
		}
		}
		viewx = 400+(-oPlayer.x);
		viewy = 300+(-oPlayer.y);
		oMapMaker.makeMap(oPlayer.x+16, oPlayer.y+16);
		//Check collisions for all blocks test
		for(int p = 0; p<20;p++)
		{
			for(int i = 0; i<48;i++)
			{
				oPlayer.checkCollision(oMapMaker.oRoomCreator[p].oBlock[i].x, oMapMaker.oRoomCreator[p].oBlock[i].y);
			}
		}
		
		}
		//fps
		avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
		if( avgFPS > 2000000 )
		{
			avgFPS = 0;
		}
		
		
		++countedFrames;

		//If frame finished early
		
		/* {{{ DRAW */
		if( frameTicks < SCREEN_TICK_PER_FRAME )
		{
			//Wait remaining time
			//SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
			
			
			/* {{{ DRAW HERE */
			// Draw background
			
			
			renderTexture(sBackground, renderer, 0, 0);
			
			// Menu and points and stuff
			oGame.draw(renderer, sMenuOverlay, sMenuSelector, sAboutOverlay);

			oMapMaker.draw(renderer, sRectangle, sEnemy);//new sprite later
			//Player
			oPlayer.draw(renderer, sPlayer,sHealthbar);
			
			//oSpawner.draw(renderer, sEnemy);
			
			renderTexture(msgInfo, renderer, 10, 10);
			
			//}/* }}} */
			//render texture
			SDL_RenderPresent(renderer);
		}
		/* }}} */
	}
	
	//destroy everything
	SDL_DestroyTexture(sRectangle);
	SDL_DestroyTexture(sBackground);
	SDL_DestroyTexture(msgInfo);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;

}
