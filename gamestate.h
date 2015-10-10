//Player Header
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class cGameState
{
	public:
	/* Gamestates
	 * 0 = intro
	 * 1 = pause/menu
	 * 2 = playing
	 * 3 = exit
	*/
	int state;
	int playerOnePoints;
	int playerTwoPoints;
	
	void create()
	{
		// Initialize points to 0
		playerOnePoints = 0;
		playerTwoPoints = 0;
		// First state is intro
		state = 0;
	}

	void pause()
	{
		state = 1;
	}

	void resume()
	{
		state = 2;
	}

	// Handles events
	void run(SDL_Event event)
	{
		//KEYPRESSTEST
		while (SDL_PollEvent(&event)) {
			//Kepresses, works like a charm! <3<3<3<3<3
			switch(event.type){
				case SDL_KEYUP:
					if(event.key.keysym.sym==SDLK_ESCAPE)
					{
						state = 1;
						break;
					}
				}
		}
		if(gameState == 1) {
			switch(event.type) {
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_UP)
				{

				}
	}
	
	// Draws to renderer
	void draw(SDL_Renderer *ren)
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
