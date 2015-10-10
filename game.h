//Player Header
#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class cGame
{
	public:
	/* Gamestates
	 * 0 = intro
	 * 1 = pause/menu
	 * 2 = playing
	 * 3 = exit
	*/
	int gameState;
	int playerOnePoints;
	int playerTwoPoints;
	
	void create()
	{
		playerOnePoints, playerTwoPoints, gameState = 0;
	}
	void run(SDL_Event event)
	{
		//KEYPRESSTEST
		while (SDL_PollEvent(&event)) {
			//Kepresses, works like a charm! <3<3<3<3<3
			switch(event.type){
				case SDL_KEYUP:
					if(event.key.keysym.sym==SDLK_ESCAPE)
					{
						gameState = 1;
						break;
					}
				}
		}
	}
	void draw(SDL_Renderer *ren, SDL_Texture *sPlayer)
	{
		//Draw Code
		// Draw the intro thingie
		if (gameState == 0)
		{
			// Draw intro here
		}
		
		// Draw menu if we're in the pause/menu state
		if(gameState == 1)
		{
			//Draw menu here
		}

		if(gameState == 2)
		{
			// Draw points and overlay here
		}

		if (gameState == 3)
		{
			// Destroy stuff, exit
			return 0;
		}

	}
};

#endif
