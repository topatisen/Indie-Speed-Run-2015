/*////////////////////////
SDL-BASE
topatisen
////////////////////////*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
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

bool playLevel;
int globR;
int globG;
int globB;

int enemyCheck;
int enemyAmount;
#include "utilities.h"
#include "gamestate.h"
#include "player.h" //player-header
#include "block.h" //block-header, also dungeon generator

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 960



const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

//music
Mix_Music *sndIntro = NULL;
Mix_Music *sndLevel = NULL;


int main(int argc, char *argv[]) {
playerHealth = 1;
enemyCheck = 0;
enemyAmount = 0;

bool levelCleared = false;

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
	//SAMPLE TRY
	Mix_Chunk *sndShoot = NULL;		//Pointer to our sound, in memory
	int channel;				//Channel on which our sound is played
	  
	int audio_rate = 22050;			//Frequency of audio playback
	Uint16 audio_format = AUDIO_S16SYS; 	//Format of the audio we're playing
	int audio_channels = 2;			//2 channels = stereo
	int audio_buffers = 4096;	
	if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		printf("Unable to initialize audio: %s\n", Mix_GetError());
		exit(1);
	}
	sndShoot = Mix_LoadWAV("sndShoot.wav");
	//channel = Mix_PlayChannel(-1, sndShoot, 0);
	TTF_Init();
	IMG_Init(1);
	//audio
	//Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
		sndIntro = Mix_LoadMUS( "sndIntro.ogg" );
		sndLevel = Mix_LoadMUS( "sndBaseLoop.ogg" );

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
	fFont = TTF_OpenFont("font.ttf", 14);
	SDL_Color black = {0, 0, 0};
	SDL_Color white = {255, 255, 255};
	//}/* }}} */
	SDL_Texture* msgInfo = createTextMessage(fFont, white, "SDL Base", renderer);
	
	//{/* {{{ SDL event */
	SDL_Event e;
	//}/* }}} */
	globR = 100;
	globG = 100;
	globB = 100;
	/* {{{ Textures */
	SDL_Texture *sEnemy = loadTexture("sEnemy.png", renderer);
	SDL_Texture *sGoal = loadTexture("sGoal.png", renderer);
	SDL_Texture *sBullet = loadTexture("sBullet.png", renderer);
	SDL_Texture *sRectangle = loadTexture("sRectangle.png", renderer);
	SDL_Texture *sBlock = loadTexture("sBlock.png", renderer);
	SDL_Texture *sHealthbar = loadTexture("sRectangle.png", renderer);
	SDL_Texture *sRBar = loadTexture("sRectangle.png", renderer);
	SDL_Texture *sGBar = loadTexture("sRectangle.png", renderer);
	SDL_Texture *sBBar = loadTexture("sRectangle.png", renderer);
	SDL_Texture *sPlayer= loadTexture("sPlayer.png", renderer);
	SDL_Texture *sBackground = loadTexture("sBackground.png", renderer);
	SDL_Texture *sBlackBackground = loadTexture("sBlackBackground.png", renderer);
	SDL_Texture *sMenuOverlay = loadTexture("sMenuOverlay.png", renderer);
	SDL_Texture *sMenuSelector = loadTexture("sMenuSelector.png", renderer);
	SDL_Texture *sAboutOverlay = loadTexture("sAboutOverlay.png", renderer);
	SDL_Texture *sElevatorScreen = loadTexture("sElevatorScreen.png", renderer);
	SDL_Texture *sDieScreen = loadTexture("sDieScreen.png", renderer);
	SDL_Texture *sControlscreen = loadTexture("sControlscreen.png", renderer);
	SDL_Texture *sControls = loadTexture("sControls.png", renderer);
	SDL_Texture *sIntroscreen = loadTexture("sIntroscreen.png", renderer);
	SDL_Texture *sEnding = loadTexture("sEnding.png", renderer);
	SDL_Texture *sBarLay = loadTexture("sBarLay.png", renderer);
	SDL_Texture *levelMsg;
	SDL_Texture *enemyMsg;
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
	
	int levelTimer = 180;
	bool nextLevel = false;
	bool restart = false;
	
	bool elevator = false;
	bool dead = false;
	bool ending = false;
	
	int elevTimer = 10;
	int dieTimer = 10;
	int endTimer = 0;
	
	int level = 0;

	
	playLevel = false;

	int musicTimer = 2040;
	Mix_PlayMusic( sndLevel, -1 );


	char levelTxt[10];
	char enemyTxt[30];

	//while not quitting (gameloop)
	while(oGame.state != 4) {
		//fps
		int frameTicks = capTimer.getTicks();

		// Empty event queueueueueu
		SDL_PumpEvents();
		
		/* {{{ Keyboard presses, mouse events osv.*/
		const Uint8 *keyboardstate = SDL_GetKeyboardState(NULL);

		// Set level
		sprintf(levelTxt,"Level: %i",level);
		sprintf(enemyTxt,"%i enemies left", 80-enemyCheck);
		//cleared level
		if(enemyCheck > 80)
		{
			levelCleared = true;
		}
		//printf("%lu\n", enemyCheck);
		//printf("%lu\n", enemyAmount);
		
		if(playerHealth < 0)
		{
			enemyCheck = 0;
			dead = true;
			restart = true;
		}
		if(restart == true)
		{
				dieTimer = 10;
				nextLevel = true;
				enemyCheck = 0;
				enemyAmount = 0;
				oMapMaker.create();
				oPlayer.x = 736;
				oPlayer.y = 536;
				restart = false;
		}
		
		if(levelCleared == true)
		{
			
			if(oPlayer.x+32>-768&&oPlayer.x < -736&&oPlayer.y+32>-568&&oPlayer.y<-536)
			{
				elevTimer = 10;
				nextLevel = true;
				enemyCheck = 0;
				enemyAmount = 0;
				oMapMaker.create();
				oPlayer.x = 736;
				oPlayer.y = 536;
				elevator = true;
				level ++;
				levelCleared = false;
			}
		
		}
		//Logical, magical!
			
		if(globR < 0)
		globR = 0;
		if(globG < 0)
		globG = 0;
		if(globB < 0)
		globB = 0;
		if(globR > 254)
		globR = 254;
		if(globG > 254)
		globG = 254;
		if(globB > 254)
		globB = 254;
		oGame.run(keyboardstate, countedFrames);
		if((oGame.state == 2))
		{
		oMapMaker.makeMap(oPlayer.x+16, oPlayer.y+16);
		oPlayer.run(event, sndShoot);

		if(level == 9)

		{
			ending = true;
		}
		
		//run spawner
		if(elevator == true)
			{
				if(elevTimer > 0)
				{
					elevTimer --;
				}
				else
				{
					SDL_Delay(3000);
					elevator = false;
					elevTimer = 10;
				}
				
			}
		if(ending == true)
			{
				if(endTimer > 0)
				{
					endTimer --;
				}
				else
				{
					SDL_Delay(6000);
					ending = false;
					endTimer = 10;
				}
				
			}
		if(dead == true)
			{
				if(dieTimer > 0)
				{
					dieTimer --;
				}
				else
				{
					SDL_Delay(3000);
					dead = false;
					dieTimer = 10;
				}
				
			}
		//check collisions enemies -> blocks
		for(int t = 0; t<10;t++)
		{
		for(int p = 0; p<10;p++)
		{
			for(int i = 0; i<48;i++)
			{
				for(int g = 0; g<8;g++)
				{
					oMapMaker.oRoomCreator[p].oSpawner.oEnemy[g].checkCollision(oMapMaker.oRoomCreator[t].oBlock[i].x+8, oMapMaker.oRoomCreator[t].oBlock[i].y+8,18);
				}
			}
		}
		}
		//check collisions enemies -> bullets
		
		for(int p = 0; p<10;p++)
		{
			for(int i = 0; i<8;i++)
			{
				for(int g = 0; g<8;g++)
				{
					oMapMaker.oRoomCreator[p].oSpawner.oEnemy[g].checkCollisionBullet(oPlayer.oBullet[i].x+8, oPlayer.oBullet[i].y+8,24);
					oPlayer.oBullet[i].checkCollision(oMapMaker.oRoomCreator[p].oSpawner.oEnemy[g].x, oMapMaker.oRoomCreator[p].oSpawner.oEnemy[g].y,4);
					
				}
			}
		}
		
		viewx = 320+(-oPlayer.x);
		viewy = 240+(-oPlayer.y);

		//Check collisions for all blocks test
		for(int p = 0; p<10;p++)
		{
			for(int i = 0; i<48;i++)
			{
				oPlayer.checkCollision(oMapMaker.oRoomCreator[p].oBlock[i].x, oMapMaker.oRoomCreator[p].oBlock[i].y);
			}
		}
		//bullet checking solids
		for(int t = 0; t<8;t++)
		{
		for(int p = 0; p<10;p++)
		{
			for(int i = 0; i<48;i++)
			{
				oPlayer.oBullet[t].checkCollision(oMapMaker.oRoomCreator[p].oBlock[i].x+8, oMapMaker.oRoomCreator[p].oBlock[i].y+8,10);
				oMapMaker.oRoomCreator[p].oBlock[i].checkCollision(oPlayer.oBullet[t].x-8,oPlayer.oBullet[t].y-8);
			}
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
			levelMsg = createTextMessage(fFont, {255,255,255}, levelTxt, renderer);
			enemyMsg = createTextMessage(fFont, {255,255,255}, enemyTxt, renderer);
			//Wait remaining time
			//SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
			
			
			/* {{{ DRAW HERE */
			// Draw background
			
			renderTexture(sBlackBackground, renderer, 0, 0);
			renderTexture(sBackground, renderer, -801+viewx, -610+viewy);
			
			// Menu and points and stuff

			oMapMaker.draw(renderer, sBlock, sEnemy);//new sprite later
			//Player

			oPlayer.draw(renderer, sPlayer,sHealthbar, sBullet, sRBar, sGBar, sBBar, fFont, sBarLay);
			oGame.draw(renderer, sMenuOverlay, sMenuSelector, sAboutOverlay, sIntroscreen, sControlscreen);
			renderTexture(sGoal, renderer, -736+viewx, -568+viewy);
			
			//oSpawner.draw(renderer, sEnemy);
			
			//renderTexture(msgInfo, renderer, 10, 10);
			if(oGame.state == 2)
			{
				renderTexture(levelMsg, renderer, 20, 20);
				renderTexture(enemyMsg, renderer, 20, 40);
			}
			if(oGame.state == 1)
			{
				renderTexture(sControls, renderer, 400, 300);
			}
			if(elevator == true)
			{
				renderTexture(sElevatorScreen, renderer, 0, 0);
			}
			if(dead == true)
			{
				renderTexture(sDieScreen, renderer, 0, 0);
			}
			if(ending == true)
			{
				renderTexture(sEnding, renderer, 0, 0);
			}
			//}/* }}} */
			//render texture
			SDL_RenderSetScale(renderer,
                       2,
                       2);
			SDL_RenderPresent(renderer);
		}
		/* }}} */
	}
	
	//destroy everything
	Mix_CloseAudio();
	SDL_DestroyTexture(sRectangle);
	SDL_DestroyTexture(sBackground);
	SDL_DestroyTexture(msgInfo);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;

}
